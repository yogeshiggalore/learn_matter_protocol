/*
  L298N motor library code
*/

#include "L298N.h"

L298N m1(D0,D1,A0, 0, 255);
L298N m2(D2,D3,A4, 0, 255);
int speed = 0;
int count=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  m1.begin();
  m2.begin();
}

void loop()
{
  m1.Control_Speed(L298N_DIR_FORWARD, speed);
  m2.Control_Speed(L298N_DIR_FORWARD, speed);
  Serial.println(speed);
  delay(2000);
  speed += 10;
  if( speed > 100 )
  {
    speed = 0;
  }
}
