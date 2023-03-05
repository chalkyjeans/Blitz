#include "autons.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern pros::Motor rollerIntakeMotor;
extern pros::Motor flywheelMotor;
extern pros::ADIDigitalOut expansion;

extern bool flywheelToggle;
extern bool boost;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

void driver();
void rollerIntake();
void flywheel();
void expansionToggle();