 #define left_motor_forward 9
#define left_motor_backward 3
#define right_motor_forward 11
#define right_motor_backward 10

#define set_point 2000
#define max_speed 255 //set Max Speed Value
#define Kp .01 //set Kp Value
#define Ki 0 //set Ki Value
#define Kd .9 //set Kd Value

int proportional=0;
int integral=0;
int derivative=0;
int last_proportional=0;
int right_speed=0;
int left_speed=0;
int sensors_sum=0;
int sensors_average=0;
int sensors[5]={0,0,0,0,0};
int Position=0;
int error_value=0;

int s1 = 4; 
int s2 = 2;
int s3 = 6;
int s4 = 7;
int s5 = 5;
void setup()
{
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
  
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  Serial.begin(9600);
}

void Stop()
{
  Serial.println("Stop");
  analogWrite(left_motor_forward,0);
  analogWrite(right_motor_forward,0);
  analogWrite(left_motor_backward,0);
  analogWrite(right_motor_backward,0);
}

void forward()
{ 
  Serial.println("Forward");
  analogWrite(left_motor_forward,150);
  analogWrite(right_motor_forward,150);
  analogWrite(left_motor_backward,0);
  analogWrite(right_motor_backward,0); 
}

void ba(int sp)
 {
     analogWrite(left_motor_forward,0);
     analogWrite(left_motor_backward,sp);
     analogWrite(right_motor_forward,0); // backward
     analogWrite(right_motor_backward,sp);  
}
void la(int sp)
 {
     analogWrite(left_motor_forward,0);
     analogWrite(left_motor_backward,0);
     analogWrite(right_motor_forward,sp); 
     analogWrite(right_motor_backward,0);    
}
void ra(int sp)
 {
     analogWrite(left_motor_forward,sp);
     analogWrite(left_motor_backward,0);
     analogWrite(right_motor_forward,0); 
     analogWrite(right_motor_backward,0);
 }  

 void ua(int sp)
 {
     analogWrite(left_motor_forward,sp);
     analogWrite(left_motor_backward,0);
     analogWrite(right_motor_forward,0); 
     analogWrite(right_motor_backward,sp);
 }  

void pid_calc() 
{
   
  
  proportional=Position-set_point;
  integral = integral + proportional; 
  derivative = proportional - last_proportional; 
  last_proportional = proportional;    
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd); 
}
void calc_turn() 
{  
                                              //Restricting the error value between +256. 
if (error_value< -256)     
  { 
error_value = -256; 
  }  
if (error_value> 256) 
  { 
error_value = 256; 
  }  
                                              // If error_value is less than zero calculate right turn speed values 
if (error_value< 0) 
  { 
left_speed = max_speed + error_value; 
right_speed = max_speed;
Serial.print("left");
Serial.println(left_speed);
Serial.print("right");
Serial.println(right_speed);  

  } 
  else 
  { 
left_speed = max_speed; 
right_speed = max_speed - error_value; 
Serial.print("left");
Serial.println(left_speed);
Serial.print("right");
Serial.println(right_speed);  

  } 
}
void motor_drive (int right_speed,int left_speed)
{
  if (right_speed>255)
      right_speed=255;
  if (right_speed<0)
      right_speed=0;
  if (left_speed>255)
      left_speed=255;
  if (left_speed<0)
      left_speed=0;
   
  analogWrite(left_motor_forward,left_speed);
  analogWrite(right_motor_forward,right_speed);
  analogWrite(left_motor_backward,0);
  analogWrite(right_motor_backward,0);
}


void loop() 
{
int  sensors_average = 0; 
  sensors_sum = 0;
 int arr[10] = {s1,s2,s3,s4,s5};
  for (int i = 0; i <=4; i++) 
   {
    sensors[i] = digitalRead(arr[i]); 
    Serial.print(sensors[i]);
    sensors_average += sensors[i] * i * 1000   ;  
    sensors_sum += sensors[i];
    }
  Serial.println();
  if(sensors_sum==0)
  {
    Stop();    
  }
//  
//  if(sensors[0]==1 and sensors[1] ==1 and sensors[4] ==0){
//  la(max_speed); // 90 
//   delay(300);
//  }
//  
//   else if(sensors[0]==0 and sensors[3]==1 and sensors[4] ==1 ){
//    ra(max_speed); // 90
//     delay(300);
//    }
               
 if(sensors_sum < 3500 && sensors_sum > 0)
      {
        Position = int(sensors_average / sensors_sum);
        Serial.println(Position);
        pid_calc();
        calc_turn();
        motor_drive(right_speed,left_speed);
      }
  
  

}
