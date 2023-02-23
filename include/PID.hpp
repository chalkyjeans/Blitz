#include "pros/motors.hpp"

extern pros::Motor flywheelMotor;

extern double flywheelkP;
extern double flywheelkI;
extern double flywheelkD;
extern double flywheelIntegralLimit;

void flywheelPID(double kP, double kI, double kD, double integralLimit);
