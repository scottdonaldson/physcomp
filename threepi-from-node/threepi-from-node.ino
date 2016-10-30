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
<<<<<<< HEAD
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
    
=======
    int value = Serial.read();  //receives message from nodeMCU
    // value should be from 0 to 10
    value -= 5;

    OrangutanMotors::setSpeeds(15 * value, -15 * value);
    
    lcd.clear();
    delay(100);
    lcd.print(value);
>>>>>>> origin/master
  }
}
  

