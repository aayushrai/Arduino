
/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
  */
#include <SPI.h>
#include <SD.h>
int count = 0;                                          // count = 0
char input[12];                                         // character array of size 12 
boolean flag = 0;    // flag =0
File myFile;
String s1;
String s2;
String rfid[50];

void get_rfid(){
  myFile = SD.open("rfid-no.txt");
  if (myFile) 
  {
        Serial.println("rfid-no.txt:");
        while (myFile.available()) 
        {
             int c = 0;
             s1 = myFile.readString();
             for(int i = 0;i<=10;i++)
                {
                 int j = s1.indexOf("\n");
                 rfid[c++] = s1.substring(0,j-1);
                 s1 = s1.substring(j+1,s1.length());
                }
        }
        for(int i = 0;i<=10;i++)
            {
             Serial.println(rfid[i]);
            }
    // close the file:
    myFile.close();
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }}

void setup()
{
         Serial.begin(9600); 
         Serial.print("Initializing SD card...");

            if (!SD.begin(4)) 
         {
            Serial.println("initialization failed!");
            while (1);
         }
            Serial.println("initialization done.");
         get_rfid();
         
         
}
void loop()
{
 

   if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 12)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         delay(5);
      }
    
      Serial.print(input);                             // Print RFID tag number 
      if((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) && 
         (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11]))
         {
            Serial.println("No Error");
            myFile = SD.open("test.txt", FILE_WRITE);
            if (myFile) 
            {   
                String a = input;
                int match = -1;
                  for(int l = 0;l<4;l++){
                    Serial.print(rfid[l]);
                    Serial.print(" == ");
                    Serial.println(a);
                  
                    if(rfid[l]==a){
                      Serial.println("match");
                      match = l;
                      }
                    }
//                Serial.print("Writing to test.txt...");
//                myFile.println(input);
//                myFile.close();
//                Serial.println("done.");
            } 
           else 
           {
            // if the file didn't open, print an error:
            Serial.println("error opening test.txt");
           }
           
         }  
        else
        {
            Serial.println("Error");
        }         
   }
}
