/*
   Matter fan example

   The example shows how to create a fan device with the Arduino Matter API.

   The example lets users control the fan through Matter and displays the values set by the user.
   The device has to be commissioned to a Matter hub first.

   Compatible boards:
   - SparkFun Thing Plus MGM240P
   - xG24 Explorer Kit

   Author: Yogesh M Iggalore
 */
#include <Matter.h>
#include <MatterFan.h>
#include "L298N.h"


MatterFan matter_fan;
L298N m1(D0,D1,A0, 0, 255);
static uint8_t fan_last_speed = 0;
uint8_t fan_current_speed = 0;
int interval_cnt=0;

void setup()
{
  Serial.begin(115200);
  Matter.begin();
  matter_fan.begin();
  m1.begin();

  Serial.println("Matter fan");

  if (!Matter.isDeviceCommissioned()) {
    Serial.println("Matter device is not commissioned");
    Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
    Serial.printf("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Serial.printf("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  }
  while (!Matter.isDeviceCommissioned()) {
    delay(200);
  }

  if (!Matter.isDeviceConnected()) {
    Serial.println("Waiting for network connection...");
  }
  while (!Matter.isDeviceConnected()) {
    delay(200);
  }
  Serial.println("Device connected");
}

void loop()
{
  
  fan_current_speed = matter_fan.get_percent();
  if (fan_current_speed != fan_last_speed) {
    fan_last_speed = fan_current_speed;
    Serial.print("Fan speed: ");
    Serial.print(fan_current_speed);
    Serial.println("%");
    m1.Control_Speed(L298N_DIR_FORWARD, fan_current_speed);
  }

  static bool fan_last_state = false;
  bool fan_current_state = matter_fan.get_onoff();

  if (fan_current_state != fan_last_state) {
    fan_last_state = fan_current_state;
    if (fan_current_state) {
      Serial.println("Fan ON");
    } else {
      Serial.println("Fan OFF");
    }
  }

  delay(100);
  interval_cnt += 100;
  if( interval_cnt > 5000 )
  {
    interval_cnt=0;
    Serial.println("heartbeat...");
  }
}
