#include <Arduino.h>
#include "L298N.h"

L298N::L298N( int in1, int in2, int ena, int ADCMin, int ADCMax )
{
	cfg.Pin_In1 = in1;
	cfg.Pin_In2 = in2;
  cfg.Pin_EnA = ena;
	cfg.DirectionA = L298N_DIR_FORWARD;
	cfg.ADCMin = ADCMin;
	cfg.ADCMax = ADCMax;
	cfg.SpeedA = 0;
}

void L298N::begin(void)
{
  pinMode(cfg.Pin_In1, OUTPUT);
  pinMode(cfg.Pin_In2, OUTPUT);
  pinMode(cfg.Pin_EnA, OUTPUT);
  TurnOff();
}

L298N::~L298N()
{

}

void L298N::TurnOff(void)
{
  Control_Speed(cfg.DirectionA, 0);
}

void L298N::Control_Speed(int direction, int speed)
{
	int val = 0;

	val = map(speed, 0, 100, cfg.ADCMin, cfg.ADCMax);
	analogWrite(cfg.Pin_EnA, val);
  if (direction == L298N_DIR_FORWARD)
  {
    digitalWrite(cfg.Pin_In1, HIGH);
    digitalWrite(cfg.Pin_In2, LOW);
  }
  else
  {
    digitalWrite(cfg.Pin_In1, LOW);
    digitalWrite(cfg.Pin_In2, HIGH);
  }
}