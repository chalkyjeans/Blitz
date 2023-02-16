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

extern pros::Motor rollerIntake;
extern pros::Motor flywheel;

extern pros::ADIDigitalOut angleChanger1;
extern pros::ADIDigitalOut angleChanger2;
extern pros::ADIDigitalOut expansion;

extern int flywheelRPM;
extern bool flywheelToggle;
extern bool angleChangerToggle;
extern bool indexerToggle;

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

void on_roller();
void off_roller();
void skills();
