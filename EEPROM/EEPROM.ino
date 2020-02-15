#include<EEPROM.h>
int val;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(10,INPUT);
pinMode(11,OUTPUT);
}
 int t =EEPROM.read(0); 
int t1 = 0;

void loop() {
  // put your main code here, to run repeatedly:
val = digitalRead(10);
if(val == 1){
  if(t1 == 0){
    if(t == 0){
    t = 1;
    }
  else{
    t = 0;
    }
    }
  
  }
 t1 = val;
 
digitalWrite(11,t);
EEPROM.write(0,t);

}
