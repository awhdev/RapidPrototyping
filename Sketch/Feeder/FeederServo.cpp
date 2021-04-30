// 
// 
// 

#include "FeederServo.h"

int delay_time = 500;
VarSpeedServo my_servo;

void FeederServo::run()
{
	my_servo.attach(servoPin);
	my_servo.write(180, 255, true);
	delay(delay_time);
	my_servo.write(0, 30, true);
	delay(delay_time);
	my_servo.detach();
}

void FeederServo::open()
{
	my_servo.attach(servoPin);
	my_servo.write(180, 255, true);
	delay(delay_time);
	my_servo.detach();
}

void FeederServo::close()
{
	my_servo.attach(servoPin);
	my_servo.write(0, 30, true);
	delay(delay_time);
	my_servo.detach();
}
FeederServo feeder_servo;

