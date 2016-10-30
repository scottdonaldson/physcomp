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
  if(Serial.available())
  {
     byte value = Serial.read();  //receives message from nodeMCU
    
    if(value==250)
    {
      while(!Serial.available())
   {}
    power = (int)Serial.read();
    while(!Serial.available())
   {}
    rotation = (int)Serial.read();
    OrangutanMotors::setSpeeds(power+rotation, power-rotation);
    }
    lcd.print(rotation);
   
  }
}
  

