
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
int count = 0;                                      
char input[12];                                          
boolean flag = 0;    
File myFile;
File myFile2;
String s1;
String s2;
String rfid[10]; 
String names[10];
int present[10];
int elementCount = 0;

void get_rfid(){
  if(SD.exists("rfid-no.txt")){
    
    Serial.println("rfid-no.txt file exists");
    }
   else
   {
     Serial.println("rfi-no.txt file not exists");
    }
    
  myFile = SD.open("rfid-no.txt");
  if (myFile) 
  {
        Serial.println("rfid-no.txt:");
        while (myFile.available()) 
        {
             int c = 0;
             s1 = myFile.readString();
             for(int i = 0;i<3;i++)
                {
                 int j = s1.indexOf("\n");
                 rfid[c++] = s1.substring(0,j-1);
                 s1 = s1.substring(j+1,s1.length());
                }
        }
        for(int i = 0;i<3;i++)
            {
             Serial.println(rfid[i]);
            }
    // close the file:
    
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening rfid-no.txt");
  }
  myFile.close();
  }

  
void get_names()
{
  if(SD.exists("name.txt"))
  {
    Serial.println("name.txt file exists");
    }
   else
   {
     Serial.println("name.txt file not exists");
    }
    
  myFile2 = SD.open("name.txt");
  if (myFile2) 
  {
        Serial.println("name.txt:");
        while (myFile2.available()) 
        {
             int p = 0;
             s2 = myFile2.readString();
             for(int i = 0;i<3;i++)
                {
                 int m = s2.indexOf("\n");
                 names[p++] = s2.substring(0,m-1);
                 s2 = s2.substring(m+1,s2.length());
                }
        }
        for(int i = 0;i<3;i++)
            {
             Serial.println(names[i]);
            }
    
  } 
  else 
  {
  
    Serial.println("error opening name.txt");
  }
  myFile2.close();
  } 


void write_attendence(bool exits,int match)
{

  myFile = SD.open("atten.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
       Serial.print("Writing to atten.txt...");
    if(exits){
    myFile.print("Leave: ");
    myFile.println(names[match]);
    }
    else{
    myFile.print("Entry: ");
    myFile.println(names[match]);
      }
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening atten.txt");
  }
  } 


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
             get_names();
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
                String a = input;
                int match = -1;
                  for(int l = 0;l<3 ;l++){   // matching id with all existing rfid's
                    if(rfid[l]==a){
                      Serial.println("match");
                      match = l;
                      }
            }
            if(match != -1){
              Serial.println(names[match]);   // if match found then print match name
              }
              bool p = false;
   /* entry exit code , first check person inside room or not,present array consist person inside room 
    if person inside room then remove it from array ,if person not inside room then put it into (present)array*/
             for(int n = 0;n<elementCount ;n++)     
             {                                      
                  if(present[n] == match){
                      p = true;
                      int r = n;
                      for(int r = n;r<elementCount ;r++){
                      present[r] = present[r+1];
                      elementCount -= 1;
                      }
                    
                      break;}
                      }
            if(p==true){
               Serial.println("bye");
              }
            else{
              if(match != -1)
                  {
                  present[elementCount]= match;
                  Serial.println("welcome");
                  elementCount += 1;
                  }
              }
            write_attendence(p,match);
              } 
        else
        {
            Serial.println("Error");
        }
    Serial.println("-----------------------------------------");         
   }
}
