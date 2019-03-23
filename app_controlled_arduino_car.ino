
#include <Servo.h>
#include <NewPing.h>

//L298N control pins
const int LMF=12;
const int LMB=13;
const int RMB=11;
const int RMF=10;

 //Sensor pins
 #define trig_pin A1
 #define echo_pin A2

 #define maximum_distance 200
 boolean goesForward=false;
 int distance=100;

 NewPing sonar(trig_pin, echo_pin, maximum_distance);
 Servo servo_motor;
void setup() {
  // put your setup code here, to run once:
pinMode(RMF, OUTPUT);
pinMode(LMF, OUTPUT);
pinMode(LMB, OUTPUT);
pinMode(RMB, OUTPUT);

servo_motor.attach(10);

servo_motor.write(115);
delay(2000);
distance=readPing();
delay(100);
distance=readPing();
delay(100);
distance=readPing();
delay(100);
distance=readPing();
delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
int distanceRight=0;
int distanceLeft=0;
delay(50);

if(distance<=20)
{
  moveStop();
  delay(300);
  moveBackward();
  delay(400);
  moveStop();
  delay(300);
  distanceRight=lookRight();
  delay(300);
  distanceLeft=lookLeft();
  delay(300);

  if(distance>=distanceLeft)
  {
    turnRight();
    moveStop();
  }
  else
  {
    turnLeft();
    moveStop();
  }
}
else
{
  moveForward();
}
distance=readPing();
}
int lookRight()
{
  servo_motor.write(50);
  delay(500);
  int distance=readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int distance=readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing()
{
  delay(70);
  int cm=sonar.ping_cm();
  if(cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop()
{
  digitalWrite(RMF, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(RMB, LOW);
  digitalWrite(LMB, LOW);
}

void moveForward()
{
  if(!goesForward)
  {
    goesForward=true;

    digitalWrite(LMF, HIGH);
    digitalWrite(RMF, HIGH);

    digitalWrite(LMB, LOW);
    digitalWrite(RMB, LOW);
  }
}

void moveBackward()
{
  goesForward=false;
  
  digitalWrite(LMB, HIGH);
  digitalWrite(RMB, HIGH);

  digitalWrite(LMF, LOW);
  digitalWrite(RMF, LOW);
}

void turnRight()
{
  digitalWrite(LMF, HIGH);
  digitalWrite(RMB, HIGH);

  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);

  delay(500);

  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);

  digitalWrite(LMB, LOW);
  digitalWrite(RMB, LOW);
}

void turnLeft()
{
  digitalWrite(LMB, HIGH);
  digitalWrite(RMF, HIGH);

  digitalWrite(LMF, LOW);
  digitalWrite(RMB, LOW);

  delay(500);

  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);

  digitalWrite(LMB, LOW);
  digitalWrite(RMB, LOW);
}
