#pragma once

#include "EZ-Template/drive/drive.hpp"

extern int DRIVE_SPEED;
extern int TURN_SPEED;
extern int SWING_SPEED;

extern double flywheelkP;
extern double flywheelkI;
extern double flywheelkD;
extern double flywheelIntegralLimit;

extern Drive chassis;

extern pros::Motor rollerIntakeMotor;
extern pros::Motor flywheelMotor;

extern pros::ADIDigitalOut expansion;

extern bool flywheelToggle;
extern bool rollerIndexerToggle;

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void exit_condition_defaults();
void modified_exit_condition();

void test();

void on_roller();
void off_roller();
void double_roller();
void skills();