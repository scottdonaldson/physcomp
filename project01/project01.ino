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
int speed = 0;

bool debug = true;

void setup() {
  robot.init(2000);
}

int setSpeed(int target) {

  OrangutanLCD::print("speed ");
  OrangutanLCD::print(speed);

  if ( speed == target ) return 0;
  
  if ( speed > target ) {
    speed -= 1;
  } else if ( speed < target ) {
    speed += 1;
  }

  OrangutanMotors::setSpeeds(speed, -1 * speed);
  delay(100);

  OrangutanLCD::clear();

  return setSpeed( target );
}

void normalBehavior() {
  speed = count % 20 < 10 ? 0 : 25;
  OrangutanMotors::setSpeeds(speed, -1 * speed);
}

void reactionBehavior() {
  setSpeed(0);
  delay(1000);
  setSpeed(60);
  delay(2500);
  setSpeed(0);
  delay(2000);
}

void loop() {

  bool isOn = digitalRead(PIN_DETECT);

  if ( debug ) {

    // at 100, go into reaction behavior, otherwise normal
//    if ( count != 100 ) {
//      normalBehavior();
//    } else {
//      reactionBehavior();
//    }

    if (isOn) {
      OrangutanMotors::setSpeeds(20, -20);
    } else {
      OrangutanMotors::setSpeeds(0, 0);
      delay(2500);
    }

    OrangutanLCD::print(isOn);
    delay(50);
    OrangutanLCD::clear();
    
  } else {
    
    // if beam gets broken (if something passes
    // in front of it) move forward and back
    if ( !isOn ) {
      reactionBehavior();
    } else {
      normalBehavior();
    }
  }
  
  count++;
}
