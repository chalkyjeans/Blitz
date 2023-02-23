#include "drivercontrol.hpp"
#include "pros/misc.h"

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

  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    flywheelToggle = !flywheelToggle;
  }

  if (flywheelToggle) {
    flywheelMotor.move_velocity(600);
  } else {
    flywheelMotor.move_velocity(0);
  }

}

void expansionToggle() {

  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
      master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
    expansion.set_value(true);
  }

}