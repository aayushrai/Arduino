#include<SoftwareSerial.h>
SoftwareSerial BT(9,10);  //TX ,RX
String readdata;
bool parking_flag = false;
void setup() {
  // put your setup code here, to run once:
BT.begin(9600);
Serial.begin(9600);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT); //front blue led
pinMode(11,OUTPUT); //back red led
pinMode(12,OUTPUT); // horn 
}

void loop() {
  // put your main code here, to run repeatedly:
 while(BT.available()){
  delay(10);
  char c = BT.read();
  readdata += c;
  }
 if(readdata.length()>0){
   Serial.println(readdata);
  if(readdata == "SS"){
    s();
    }
  else if(readdata == "FF"){
    f();
    }
  else if(readdata == "BB"){
    b();
    }
  else if(readdata == "LL"){
    l();
    }
  else if(readdata == "RR"){
    r();
    }
  if(readdata == "SWS"){ //front blue
    digitalWrite(8,HIGH);
    }
  if(readdata == "SwS"){
    digitalWrite(8,LOW);
    }
   if(readdata == "SUS"){ //front blue
    digitalWrite(11,HIGH);
    }
  if(readdata == "SuS"){
    digitalWrite(11,LOW);
    }
 
   if(readdata == "SVS"){
    digitalWrite(12,HIGH);
    }
    if(readdata == "SvS"){
    digitalWrite(12,LOW);
    }
// if(readdata == "SXS"){
//    parking_flag = true;
//    }
//  if(readdata == "SxS"){
//     parking_flag = false;
//    }
//  if(parking_flag == true){
//      digitalWrite(8,HIGH);
//     digitalWrite(11,HIGH);
//     delay(500);
//     digitalWrite(8,LOW);
//     digitalWrite(11,LOW);
//     readdata = ""; 
//    }
  }
  readdata = ""; 
}


void f()
 {
 digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
   digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
}
void s()
 {
 digitalWrite(2,LOW);
  digitalWrite(3,LOW);
   digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}
void b()
 {
 digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
   digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
}
void l()
 {
 digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
   digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
}
void r()
 {
 digitalWrite(2,LOW);
  digitalWrite(3,HIGH);  
   digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
 }  
