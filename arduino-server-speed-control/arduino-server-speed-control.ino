/**
* Arduino Server Speed Control 0.0.1
* A very simple demo for controlling the speed of a server via a poti
* 
* Copyright 2019, Murat Motz
* Murat Motz <dev@ztom.de> (https://www.kmgt.de)
*/

// include server lib
#include <Servo.h> 

// create servo object
Servo servo;

// digital pin number of server
int servoPin = 1;

// default server positionen
int servoLeftPosition = 0;
int servoRightPosition = 180;

// digital pin number of poti
int potiPin = 2;

// speed (numbers are loop ticks)
int moveSpeedCurrent = 15;
int moveSpeedMax = 30;

// helper variable for server position
int pos = 0;

// counter for runtime loop
int loopNum = 0;

// delay time between runtime loops in milliseconds
int loopDelay = 1000;

// calculate the current server move speed
void calcMoveSpeed() 
{
  // read poti
  float potiValue = analogRead(potiPin);
  if (potiValue < 1) potiValue = 1;
  if (potiValue > 1000) potiValue = 1000;
  
  // calculate the new current move speed
  moveSpeedCurrent = round((potiValue / 1000) * moveSpeedMax);
}

void setup() 
{
  Serial.begin(9600);
  // register servo
  servo.attach(servoPin);
} 

void loop() 
{
  // count runtime loops
  loopNum++;
  
  // first loop
  if(loopNum == 1)
  {
    // move servo to left on first loop
    servo.write(servoLeftPosition);
  }

  // read poti and set current move speed
  calcMoveSpeed();
  
  // move servo to right
  for (pos = servoLeftPosition; pos <= servoRightPosition; pos += 1)
  {
    servo.write(pos);
    delay(moveSpeedCurrent);
  }

  // read poti and set current move speed
  calcMoveSpeed();

  // move servo to left
  for (pos = servoRightPosition; pos >= servoLeftPosition; pos -= 1)
  {
    servo.write(pos);
    delay(moveSpeedCurrent);
  }

  // some delay before next loop
  delay(loopDelay);
}
