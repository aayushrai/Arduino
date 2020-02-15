
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(9,INPUT); 
pinMode(10,INPUT); 
pinMode(11,INPUT);
pinMode(12,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int d0 = digitalRead(9);//left
 int d1 = digitalRead(10);//right
 int d2 = digitalRead(11);//back
 int d3 = digitalRead(12);//forward
 Serial.println(d2);
 Serial.println(d1);
Serial.println(d2);
Serial.println(d3);
if(d3 == 0){
  f();
  }
else if(d2 == 0){
  b();
  }
else if(d1 == 0){
  r();
  }
else if(d0 == 0){
  l();
  }
else{
  s(); 
  }

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
