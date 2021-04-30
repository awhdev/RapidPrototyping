// FeederServo.h

#ifndef _FEEDERSERVO_h
#define _FEEDERSERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//https://github.com/netlabtoolkit/VarSpeedServo
#include <VarSpeedServo.h>

const int servoPin = 9; // the digital pin used for the servo


class FeederServo
{
 protected:

 public:
	static void run();
	static void open();
	static void close();
};

extern FeederServo feeder_servo;

#endif
