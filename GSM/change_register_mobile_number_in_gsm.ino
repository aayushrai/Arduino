 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9,8);
String msg = String(100);
String msg2 = String(100);
String msg3 = String(100);
String reg = "9893868931";
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0){
  msg = mySerial.readString();
  Serial.println(msg);
  
  msg2 = msg.substring(msg.indexOf("\n")+1,msg.length());
  msg3 = msg2.substring(msg2.indexOf("\n")+1,msg2.length());
  
  if(msg3.indexOf("Change=") != -1){
    reg = msg3.substring(msg3.indexOf("Change=")+7,msg3.indexOf("\n")-1);
     Serial.print("register mobile number changed to");
      Serial.println(reg);
    }
    
  Serial.println("=======================");
  Serial.println(msg3);
  msg  = "";
  msg2 = "";
  msg3 = "";
 }

}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91"+reg+"\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 
