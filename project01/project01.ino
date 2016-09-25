// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.  Pololu3pi.h includes all of the
// other Orangutan Arduino libraries that can be used to control the
// on-board hardware such as LCD, buzzer, and motor drivers.
#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;

// set up sensor
int PIN_DETECT = 0;
int count = 0;

bool debug = false;

void setup() {
  robot.init(2000);
}

void loop() {

  bool isOn = digitalRead(PIN_DETECT);

  if ( debug ) {

    // in debug mode, just print to LCD
    OrangutanLCD::print(isOn);
    delay(50);
    OrangutanLCD::clear();
    
  } else {
    
    // if beam gets broken (if something passes
    // in front of it) move forward and back
    if ( !isOn ) {
      OrangutanMotors::setSpeeds(60, -60);
      delay(2000);
    }
  
    OrangutanMotors::setSpeeds(0, 0);
  }
  
  count++;
}
