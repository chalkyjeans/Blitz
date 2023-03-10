#include "autons.hpp"
#include "PID.hpp"
#include "pros/rtos.hpp"


void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 1, 0, 0, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 2.5, 0, 2, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 2.5, 0, 2, 0);
  chassis.set_pid_constants(&chassis.turnPID, 0.9, 0, 0, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void indexer_test() {
  pros::Task flywheel_task([]() {
    flywheelMotor.move_velocity(565);
  });
  pros::delay(2500);
  rollerIntakeMotor.move_velocity(-600);
  pros::delay(500);
  rollerIntakeMotor.move_velocity(0);
  pros::delay(700);
  rollerIntakeMotor.move_velocity(600);
  pros::delay(300);
  rollerIntakeMotor.move_velocity(-600);
}

void roller() {
  rollerIntakeMotor.move_relative(300, 600);
  // block until the roller intake is done
  while (rollerIntakeMotor.get_actual_velocity() != 0) {
    pros::delay(10);
  }
}

void skillsroller() {
  rollerIntakeMotor.move_relative(500, 600);
  // block until the roller intake is done
  while (rollerIntakeMotor.get_actual_velocity() != 0) {
    pros::delay(10);
  }
}

void turn_test() {
  // chassis.set_turn_pid(180, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(270, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}

void drive_test() {
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(96*1.5, 70);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}

void on_roller() {

  chassis.set_drive_pid(-15, 50);
  chassis.wait_drive();

  rollerIntakeMotor.move_relative(300, 600);
  pros::delay(500);

  chassis.set_drive_pid(10, 50);
  chassis.wait_drive();

}

void off_roller() {

  chassis.set_drive_pid(-45, 70);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-22, 50);
  chassis.wait_drive();

  rollerIntakeMotor.move_relative(400, 600);
  pros::delay(500);

  chassis.set_drive_pid(10, 50);
  chassis.wait_drive();

  // chassis.set_drive_pid(30, 50);
  // chassis.wait_drive();

  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(145, 80);
  // chassis.wait_drive();

  // chassis.set_turn_pid(137, TURN_SPEED);
  // chassis.wait_drive();

  // pros::Task flywheel([]() {
  //   flywheelMotor.move_velocity(600);
  // });

  // pros::delay(2700);

  // rollerIntakeMotor.move_velocity(-600);
  // pros::delay(800);
  // rollerIntakeMotor.move_velocity(0);

  // pros::delay(500);
  // rollerIntakeMotor.move_velocity(0);
  // pros::delay(700);
  // rollerIntakeMotor.move_velocity(600);
  // pros::delay(300);
  // rollerIntakeMotor.move_velocity(-600);

}

void pmskills() {

  // rollerIntakeMotor.move_relative(100, 600);
  // pros::delay(500);
  // rollerIntakeMotor.move_relative(-600, 600);
  // pros::delay(500);
  ///////////////////////////////////////////////
  //52 point
  chassis.set_drive_pid(50, 70);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-70, 50);
  chassis.wait_drive();

  expansion.set_value(true);
  pros::delay(500);
  expansion.set_value(false);
  pros::delay(500);
  expansion.set_value(true);
  pros::delay(500);
  expansion.set_value(false);
  pros::delay(500);
  expansion.set_value(true);

  //////////////////////////////////////////////
  // chassis.set_drive_pid(-15, 70);
  // chassis.wait_drive();
  // //skillsroller();

  // rollerIntakeMotor.move_relative(100, 600);
  // pros::delay(500);
  // chassis.set_drive_pid(-5, 70);
  // chassis.wait_drive();
  // rollerIntakeMotor.move_relative(-700, 600);
  // pros::delay(500);

  // chassis.set_drive_pid(50, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-70, 70);
  // chassis.wait_drive();

  // rollerIntakeMotor.move_relative(100, 600);
  // pros::delay(500);
  // rollerIntakeMotor.move_relative(-600, 600);
  // pros::delay(500);

  // chassis.set_drive_pid(70, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(300, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-135, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-50, 70);
  // chassis.wait_drive();
  
  // rollerIntakeMotor.move_relative(100, 600);
  // pros::delay(500);
  // rollerIntakeMotor.move_relative(-600, 600);
  // pros::delay(500);

  // chassis.set_drive_pid(70, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-50, 70);
  // chassis.wait_drive();

  // rollerIntakeMotor.move_relative(100, 600);
  // pros::delay(500);
  // rollerIntakeMotor.move_relative(-600, 600);
  // pros::delay(500);

  // //expan
  // chassis.set_drive_pid(50, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-70, 50);
  // chassis.wait_drive();

  // expansion.set_value(true);
  // pros::delay(500);
  // expansion.set_value(false);
  // pros::delay(500);
  // expansion.set_value(true);
  // pros::delay(500);
  // expansion.set_value(false);
  // pros::delay(500);
  // expansion.set_value(true);

  ///////////////////////////////////////////////////
  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-70, 50);
  // chassis.wait_drive();

  // skillsroller();

  // chassis.set_drive_pid(50, 70);
  // chassis.wait_drive();

  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(300, 80);
  // chassis.wait_drive();

  // chassis.set_turn_pid(180, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-74, 50);
  // chassis.wait_drive();

  // skillsroller();

}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}


void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}

void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}

void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}

void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}

