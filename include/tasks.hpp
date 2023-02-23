#include "autons.hpp"
#include "main.h"
#include "PID.hpp"

extern pros::Motor flywheelMotor;
extern pros::Motor rollerIntakeMotor;

extern bool flywheelToggle;
extern bool rollerIndexerToggle;

void flywheelTask();
void indexerTask();
void flywheelPIDTask();


void setupTasks();