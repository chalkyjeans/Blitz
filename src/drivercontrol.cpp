#include "drivercontrol.hpp"
#include "autons.hpp"
#include "pros/misc.h"
#include "pros/screen.hpp"

void driver() {
  int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  int finalLeft;
  int finalRight;

  if (!boost) {
    finalLeft = left * 0.8;
    finalRight = right * 0.8;
  } else {
    finalLeft = left;
    finalRight = right;
    master.rumble(".");
  }

  leftMotors.move(finalLeft);
  rightMotors.move(finalRight);

  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
    boost = !boost;
  }
  
}

void rollerIntake() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    rollerIntakeMotor.move_velocity(600);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    rollerIntakeMotor.move_velocity(-600);
  } else {
    rollerIntakeMotor.move_velocity(0);
  }
}

void flywheel() {

  int flywheelSpeed = 550;

  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    flywheelToggle = !flywheelToggle;
  }

  if (flywheelToggle) {
    flywheelMotor.move_velocity(flywheelSpeed);
  } else {
    flywheelMotor.move_velocity(0);
  }

  // make a bang bang control algorithm for the flywheel

  if (flywheelToggle) {
    if (flywheelMotor.get_actual_velocity() > flywheelSpeed) {
      flywheelMotor.move_velocity(flywheelSpeed);
    } else if (flywheelMotor.get_actual_velocity() < flywheelSpeed) {
      flywheelMotor.move_velocity(flywheelSpeed);
    } else {
      flywheelMotor.move_velocity(flywheelSpeed);
    }
  }

}

void expansionToggle() {

  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
    expansion.set_value(true);
  }

}