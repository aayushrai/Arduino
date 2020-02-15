#include <Servo.h>
Servo myser;
String val = String(10);
int maxdis = 14;
int us_val;
int us_val2;
int turn_delay = 1000;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myser.attach(8);
myser.write(90);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(8,OUTPUT); //survo
pinMode(12,OUTPUT);//us
pinMode(13,INPUT);//us

}

void loop() {

us_val = us(12,13);
Serial.println(us_val);
if(us_val>maxdis){
  f();
  }
if(us_val < maxdis){
 // s();
  delay(500);
  myser.write(170);
  delay(500); 
   us_val2 = us(12,13);
   myser.write(90);
  if(us_val2 > maxdis){
    l();
    delay(1000);
    }
  else{
  myser.write(0);
  delay(500);
   us_val2 = us(12,13);
   myser.write(90);
  if(us_val2 > maxdis){
    r();
    delay(1000);
    }
  
  }
  }
  
  }




int us(int targ,int echo){
  digitalWrite(targ,LOW);
  delayMicroseconds(3000);
  
  digitalWrite(targ,HIGH);
  delayMicroseconds(10);
  digitalWrite(targ,LOW);
  int dura = pulseIn(echo,HIGH);
  int distance = (dura*.034)/2;
//  Serial.print(echo);
//  Serial.print(" = ");
//  Serial.println(distance);
  return distance;
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
void r()
 {
 digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
   digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
}
void l()
 {
 digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
   digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
 }  
