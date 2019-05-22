  // put your setup code here, to run once:

#include <Servo.h>

 float vectorS[5] = {0, 40, 0,0,0};

float weight1[5][5] = { { 0.4682828 ,  0.14279915, -0.03936641, -0.02099363,  0.03984427 },
{ -0.22856644,  0.21864294,  0.6891374 , -0.03994741, -0.43646815 },
{ 0.00982535, -0.29163   ,  0.20969436, -0.25398114,  0.25274584 },
{ -0.04567846,  0.4421433 ,  0.14062051,  1.3523922 ,  0.19996467 },
{ -0.2307132 ,  0.8353929 , -0.04177215,  0.5711426 ,  0.03562269 } };

float weight2[5][5] = { { 0.37774515, -0.47362155,  0.23098895, -1.8944465 , -1.0863293 },
{ -0.46172467, -1.1579158 , -0.43497017, -3.9246001 , -1.2314394 },
{ 0.669023  , -2.1940145 , -0.7190236 , -1.0843403 , -1.2950823 },
{ -0.82968247, -0.18263933, -0.6766763 , -3.5336998 , -0.03752254 },
{ -1.3776823 , -2.9272099 , -0.28459144,  0.11302639, -0.56841785 } };

float bias1[5] = { -3.8868043, -1.0757042, -8.128541 ,  3.2644813,  7.429283 };
float bias2[5] = { -7.2081084 , -3.600246  , -0.25432575,  3.2756257 ,  6.7026625 };

int pinLB = 12; // define pin 12
int pinLF = 3; // define pin 3
int pinRB = 13; // define pin 13
int pinRF = 11; // define pin 11
////////////////////////////////
int inputPin = 4; // define pin for sensor echo
int outputPin =5; // define pin for sensor trig
int Fspeedd = 0; // forward speed
int Rspeedd = 0; // right speed
int Lspeedd = 0; // left speed
int directionn = 0; // forward=8 backward=2 left=4 right=6
Servo myservo; // set myservo
int delay_time = 250; // settling time after steering servo motor moving B
int Fgo = 8; // Move F
int Rgo = 6; // move to the R
int Lgo = 4; // move to the L
int Bgo = 2; // move B
void setup()
{
 Serial.begin(9600); // Define motor output pin
 pinMode(pinLB,OUTPUT); // pin 12
 pinMode(pinLF,OUTPUT); // pin 3 (PWM)
 pinMode(pinRB,OUTPUT); // pin 13
 pinMode(pinRF,OUTPUT); // pin 11 (PWM)
 pinMode(inputPin, INPUT); // define input pin for sensor
 pinMode(outputPin, OUTPUT); // define output pin for sensor
 myservo.attach(9); // Define servo motor output pin to D9 (PWM)
}
void advance() // move forward
 {
 digitalWrite(pinLB,LOW); // right wheel moves forward
digitalWrite(pinRB, LOW); // left wheel moves forward
 analogWrite(pinLF,255); 
 analogWrite(pinRF,255);
 }
void stopp() // stop
 {
 digitalWrite(pinLB,HIGH);
 digitalWrite(pinRB,HIGH);
 analogWrite(pinLF,0);
 analogWrite(pinRF,0);
 }
void right() // turn right (single wheel)
 {

 digitalWrite(pinLB,HIGH); // wheel on the left moves forward
 digitalWrite(pinRB,LOW); // wheel on the right moves backward
 analogWrite(pinLF, 255);
 analogWrite(pinRF,255);
 }
void left() // turn left (single wheel)
 {
 digitalWrite(pinLB,LOW); // wheel on the left moves backward
 digitalWrite(pinRB,HIGH); // wheel on the right moves forward
 analogWrite(pinLF, 255);
 analogWrite(pinRF,255);
 }

void back() // move backward
 {
 digitalWrite(pinLB,HIGH); // motor moves to left rear
 digitalWrite(pinRB,HIGH); // motor moves to right rear
 analogWrite(pinLF,255);
 analogWrite(pinRF,255);
 }

void ask_pin_F() // measure the distance ahead
 {
 myservo.write(90);
 digitalWrite(outputPin, LOW); // ultrasonic sensor transmit low level signal 2μs
 delayMicroseconds(2);
 digitalWrite(outputPin, HIGH); // ultrasonic sensor transmit high level signal10μs 
 delayMicroseconds(10);
 digitalWrite(outputPin, LOW); // keep transmitting low level signal
 float Fdistance = pulseIn(inputPin, HIGH); // read the time in between
 Fdistance= Fdistance/5.8/10; // convert time into distance (unit: cm)
 Fspeedd = Fdistance; // read the distance into Fspeedd
 }
 void ask_pin_L() // measure distance on the left
 {
 myservo.write(5);
 delay(delay_time);
 digitalWrite(outputPin, LOW); // ultrasonic sensor transmit low level signal 2μs
 delayMicroseconds(2);
 digitalWrite(outputPin, HIGH); // ultrasonic sensor transmit high level signal10μs, at least 10μs
 delayMicroseconds(10);
 digitalWrite(outputPin, LOW); // keep transmitting low level signal
 float Ldistance = pulseIn(inputPin, HIGH); // read the time in between
 Ldistance= Ldistance/5.8/10; // convert time into distance (unit: cm)
 Lspeedd = Ldistance; // read the distance into Lspeedd
 }
void ask_pin_R() // measure distance on the right
 {
 myservo.write(177);
 delay(delay_time);
 digitalWrite(outputPin, LOW); // ultrasonic sensor transmit low level signal 2μs
 delayMicroseconds(2);
 digitalWrite(outputPin, HIGH); // ultrasonic sensor transmit high level signal10μs, at least 10μs
 delayMicroseconds(10);
 digitalWrite(outputPin, LOW); // keep transmitting low level signal
 float Rdistance = pulseIn(inputPin, HIGH); // read the time in between
 Rdistance= Rdistance/5.8/10; // convert time into distance (unit: cm)
 Rspeedd = Rdistance; // read the distance into Rspeedd
 }
 float* relu(float arrayOfNeuron[])
{
  float arrayOfNeuron1[5];
  for (int i = 0; i < 5; i++)
  {
    if (arrayOfNeuron[i] < 0)
    {
      arrayOfNeuron1[i] = 0;
    }
    else
    {
      arrayOfNeuron1[i] = arrayOfNeuron[i];
    }
  }

  return arrayOfNeuron1;
}

float* sigmoid(float arrayOfNeuron[])
{
  float arrayOfNeuron1[5];
  for (int i = 0; i < 5; i++)
  {
    arrayOfNeuron1[i] = 1 / (1 + exp(-arrayOfNeuron[i]));
    
  }
  
  float max = 0;
  for (int i = 0; i < 5; i++)
  {
    if (arrayOfNeuron1[i]>max)
    {
      max = arrayOfNeuron1[i];
    }
  }
  for (int i = 0; i < 5; i++)
  {
    if (arrayOfNeuron1[i] == max)
    {
      arrayOfNeuron1[i] = 1;
    }
    else
    {
      arrayOfNeuron1[i] = 0;
    }
  }
  return arrayOfNeuron1;
}

float* directMotion(float startVector[])
{
  float sl1[5];
  for (int i = 0; i < 5; i++)
  {
    float count = 0;
    for (int j = 0; j < 5; j++)
    {
      count += weight1[j][i] * startVector[j];
    }
    sl1[i] = count + bias1[i];

  }
  float SL1[5];
  memcpy(SL1, relu(sl1), sizeof(SL1));
  float sl2[5];
  float SL2[5];
  for (int i = 0; i < 5; i++)
  {
    float count = 0;
    for (int j = 0; j < 5; j++)
    {
      count += weight2[j][i] * SL1[j];
    }
    sl2[i] = count + bias2[i];

  }
  memcpy(SL2, sigmoid(sl2), sizeof(SL2));

  return SL2;

}


void loop() {
  // put your main code here, to run repeatedly:
 myservo.write(90); // home set the servo motor, ready for next measurement
int result=0;
float answer[5];
  memcpy(answer, directMotion(vectorS), sizeof(answer));
  for (int i = 0; i < 5; i++)
  {
    if(answer[i]==0)
    {
      result=i;
    }
  }

if (result==0)//Forward
{
 advance(); // move forward
 delay(100);
 stopp();
 ask_pin_F();
for(int i=0;i<5;i++)
  {
    vectorS[i]=0;
  }
  vectorS[1] = Fspeedd; 
  
}
else if(result==1 || result==4)//stop and back
{
  stopp();
  back();
  delay(100);
  ask_pin_L();
  ask_pin_R();
      for(int i=0;i<5;i++)
  {
    vectorS[i]=0;
  }
  vectorS[0] = Lspeedd;
  vectorS[2] = Rspeedd;
  
}
else if(result==2)//Left
{
  stopp();
  left();
  delay(600);
  advance(); // move forward
  delay(100);
  ask_pin_F();
    for(int i=0;i<5;i++)
  {
    vectorS[i]=0;
  }
  vectorS[1] = Fspeedd;
}
else if( result==3)//Right
{
  stopp();
  right();
  delay(600);
  advance(); // move forward
  delay(100);
  ask_pin_F();
    for(int i=0;i<5;i++)
  {
    vectorS[i]=0;
  }
  vectorS[1] = Fspeedd;
}
else
{
  stopp();

}
}
