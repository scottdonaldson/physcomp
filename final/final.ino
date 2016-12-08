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

int t = 0;
int speed = 0;
float left = 1.0;
float right = 1.0;
int state = 0;

bool debug = false;

void setup() {
  robot.init(2000);
}

void turn(float dir) {

  // default: go straight
  left = 1.0;
  right = 1.0;
  
  // turn left
  if (dir < 0) {
    
    // [-1, 0] --> [-1, 1]
    left = (dir * 2.0) + 1.0;

  // turn right
  } else if (dir > 0) {

    // [0, 1] --> [1, -1]
    right = 1.0 - (dir * 2.0);
  }
}

int circleLeft() {
  turn(-0.25);
  setSpeed(40);
  delay(5000);
  return 1;
}

int circleRight() {
  turn(0.25);
  setSpeed(40);
  delay(5000);
  return 9999;
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

  OrangutanMotors::setSpeeds(
    (int)(left * (float)speed), 
    (int)(right * (float)speed)
  );
  
  delay(100);

  OrangutanLCD::clear();

  return setSpeed( target );
}

void behavior() {
  
  switch (state) {
    
    case 0: {
      state = circleLeft();
      break;
    }

    case 1: {
      state = circleRight();
      break;
    }
    
    default: {
      // come to a stop
      setSpeed(0);
      break;
    }
  }
}

void loop() {

  behavior();
  
  t++;
}
