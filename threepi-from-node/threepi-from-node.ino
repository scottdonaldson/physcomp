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
  if(Serial.available())
  {
    char value = Serial.read();  //receives message from nodeMCU
    
    if(value=='a')  //goes forward if 'a' is received
    {
      OrangutanMotors::setSpeeds(40, 40);
    }
    if(value=='b')  //goes backward if 'b' is received
    {
    OrangutanMotors::setSpeeds(-40, -40);
    }
    lcd.print(value);
    
  }
  
}
