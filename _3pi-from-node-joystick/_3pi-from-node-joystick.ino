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

    int power = Serial.read();  //receives message from nodeMCU
    int rotation = Serial.read();
  
    OrangutanMotors::setSpeeds(power+rotation, power-rotation);
   
    lcd.print(power);
    lcd.print(rotation);
    
  }
  

