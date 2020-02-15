int th = 500;
int Left_p=9;
int Left_n=3;
int Right_p=11;
int Right_n=10;
int spd = 255;
// best case
// white > th
// black < th
void setup() {
  
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Left_p,OUTPUT);
pinMode(Left_n,OUTPUT);
pinMode(Right_p,OUTPUT);
pinMode(Right_n,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int s1 = analogRead(A2); 
int s2 = analogRead(A3);
int s3 = analogRead(A4);
int s4 = analogRead(A5);
int s5 = analogRead(A6);
int s6 = analogRead(A7);
if(s1<th and s2 <th and s4<th and s5 < th and s3< th){
  la(spd); // T
  delay(240);
  }
if(s1<th and s2 <th and s3<th and s6 < th and s4> th and s5>th){
  la(spd); // F
  delay(240);
  }
  
  
if(s1>th and s2 >th and s3< th and s4>th and s5 > th){
  fa(spd);
  }

if(s1>th and s2 <th and s3>th and  s4>th and s5 > th){
  la(spd);
  }
  
if(s1>th and s2 >th and s3>th and s4<th and s5 > th){
  ra(spd);
  }
  
if(s1<th and s2 <th and s4>th and s5 > th and s6>th){
  la(spd); // 90 
   delay(40);
  }
  
if(s1>th and s2 >th and s4<th and s5 < th and s6>th ){
  ra(spd); // 90
   delay(40);
  }


}

 void fa(int sp)
 {
  analogWrite(Left_p,sp);
   analogWrite(Left_n,0);
   analogWrite(Right_p,sp);// forward
   analogWrite(Right_n,0);
     
}

void ba(int sp)
 {
analogWrite(Left_p,0);
     analogWrite(Left_n,sp);
     analogWrite(Right_p,0); // backward
     analogWrite(Right_n,sp);  
}
void la(int sp)
 {
 analogWrite(Left_p,0);
     analogWrite(Left_n,0);
     analogWrite(Right_p,sp); 
     analogWrite(Right_n,0);    
}
void ra(int sp)
 {
  analogWrite(Left_p,sp);
     analogWrite(Left_n,0);
     analogWrite(Right_p,0); 
     analogWrite(Right_n,0);
 }  

 void ua(int sp)
 {
  analogWrite(Left_p,sp);
     analogWrite(Left_n,0);
     analogWrite(Right_p,0); 
     analogWrite(Right_n,sp);
 }  

 void display(int s1,int s2,int s3,int s4 ,int s5){
  Serial.print(s1);
  Serial.print(" ");
  Serial.print(s2);
  Serial.print(" ");
  Serial.print(s3);
  Serial.print(" ");
  Serial.print(s4);
  Serial.print(" ");
  Serial.println(s5);

  }
  
