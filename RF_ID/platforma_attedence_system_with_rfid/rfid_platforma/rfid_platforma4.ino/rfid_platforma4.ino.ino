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
    myFile.close();
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening rfid-no.txt");
  }}

  
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
    myFile2.close();
  } 
  else 
  {
  
    Serial.println("error opening name.txt");
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
                  for(int l = 0;l<3 ;l++){
                    if(rfid[l]==a){
                      Serial.println("match");
                      match = l;
                      }
            }
            if(match != -1){
              Serial.println(names[match]);
              }
           
         }  
        else
        {
            Serial.println("Error");
        }         
   }
}
