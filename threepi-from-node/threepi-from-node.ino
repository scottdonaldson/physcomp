#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
OrangutanLCD lcd;

void setup() {
  robot.init(2000);
  Serial.begin(9600);
}

void loop() {
  
  int power;
  int rotation;
  
  if (Serial.available()) {
    byte value = Serial.read();  //receives message from nodeMCU

    // 250 should be the start of the message
    if (value == 250) {
      
      while(!Serial.available()) {}
      power = (int)Serial.read() - 100;
      
      while(!Serial.available()) {}
      rotation = (int)Serial.read() - 100;
      
      OrangutanMotors::setSpeeds((int)(0.91 * power) + rotation, power - rotation);
    }
  }
}
  

