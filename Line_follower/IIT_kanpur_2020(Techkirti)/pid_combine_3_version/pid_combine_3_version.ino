//color sensor pins
#define S0 40   
#define S1 42
#define S2 38
#define S3 34
#define sensorOut 36
int red_frequency = 0;
int green_frequency = 0;
int frequency = 0;
int red,green;

// Ultrasonic pin
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;

//motor pins
#define left_motor_forward 3
#define left_motor_backward 9
#define right_motor_forward 10
#define right_motor_backward 11

//pid variable
#define set_point 2000
#define max_speed 255 //set Max Speed Value
#define base_speed 255
#define Kp .35 //set Kp Value
#define Ki 0 //set Ki Value
#define Kd 0.8 //set Kd Value

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

int ultrasonic(){
  
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    return(distance);
  }

int red_color_sensor(){
    // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  red_frequency = map(frequency, 25,72,255,0);
  return(red_frequency);
  }

int green_color_sensor(){
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  green_frequency = map(frequency, 30,90,255,0);
 return(green_frequency);
  }
  
void setup()
{
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);

  // Ultrasonic pin set
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // color sensor pin set
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  //ir pin set
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

void forward(int sp)
{ 
  Serial.println("Forward");
  analogWrite(left_motor_forward,sp);
  analogWrite(right_motor_forward,sp);
  analogWrite(left_motor_backward,0);
  analogWrite(right_motor_backward,0); 
}

void la(int sp)
 {
     analogWrite(left_motor_forward,0);
     analogWrite(left_motor_backward,sp);
     analogWrite(right_motor_forward,sp); 
     analogWrite(right_motor_backward,0);    
}
void ra(int sp)
 {
     analogWrite(left_motor_forward,sp);
     analogWrite(left_motor_backward,0);
     analogWrite(right_motor_forward,0); 
     analogWrite(right_motor_backward,sp);
 } 


 

int pid_calc() 
{
  proportional=Position-set_point;
  derivative = proportional - last_proportional; 
  last_proportional = proportional;    
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd); 
  return error_value;
}

int calc_turn() 
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
left_speed = base_speed + error_value; 
right_speed = base_speed - error_value;
Serial.print("left");
Serial.println(left_speed);
Serial.print("right");
Serial.println(right_speed);  

  } 
  else 
  { 
left_speed = base_speed + error_value; 
right_speed = base_speed - error_value; 
  } 
return(left_speed,right_speed);
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
Serial.print("left");
Serial.println(left_speed);
Serial.print("right");
Serial.println(right_speed);  

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

//if(sensors[0]==1 and sensors[1] ==1 and sensors[2] ==1 and sensors[4] ==0){
//    la(max_speed); // 90 
//     delay(205);
//  }
//  else if(sensors[0]==0  and sensors[2] ==1 and sensors[3] ==1 and sensors[4] ==1){
//  ra(max_speed); // 90 
//   delay(205);
//  }

red = red_color_sensor();
green = green_color_sensor();
if(red>0 and green<0){
  Stop();
  }
 else{
 if(ultrasonic()<=12){
  la(255);
  delay(830);
  }
               
 else if(sensors_sum < 3500 && sensors_sum > 0)
      {
        Position = int(sensors_average / sensors_sum);
        Serial.println(Position);
        error_value = pid_calc();
        left_speed,right_speed= calc_turn();
        motor_drive(right_speed,left_speed);
      }
  
 } 

}
