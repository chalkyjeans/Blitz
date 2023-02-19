#include "autons.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "PID.hpp"
#include <cstdio>

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void flywheelPIDTask() {
  printf("Starting flywheel PID task\n");
  pros::Task flywheelPIDTask([]() {
    while (true) {
      flywheelPID(flywheelkP, flywheelkI, flywheelkD, flywheelIntegralLimit);
    }
  });
  printf("Started flywheel PID task\n");
}

void flywheelTask() {
  printf("Starting flywheel task\n");
  pros::Task flywheelTask([]() {
    while (true) {
      if (flywheelToggle) {
        printf("Flywheel on\n");
        flywheel.move_velocity(flywheelRPM);
      } else {
        printf("Flywheel off\n");
        flywheel.move_velocity(0);
      }
      pros::delay(10);
    }
  });
}

void indexerTask() {
  printf("Starting indexer task\n");
  pros::Task indexerTask([]() {
    while (true) {
      if (indexerToggle) {
        printf("Indexer on\n");
        rollerIntake.move_velocity(600);
      } else {
        printf("Indexer off\n");
        rollerIntake.move_velocity(0);
      }
      pros::delay(10);
    }
  });
  printf("Started indexer task\n");
}

void angleChangerTask() {
  printf("Starting angle changer task\n");
  pros::Task angleChangerTask([]() {
    while (true) {
      if (angleChangerToggle) {
        printf("Angle changer up\n");
        angleChanger1.set_value(true);
        angleChanger2.set_value(true);
        flywheelRPM = 450;
      } else {
        printf("Angle changer down\n");
        angleChanger1.set_value(false);
        angleChanger2.set_value(false);
        flywheelRPM = 600;
      }
      pros::delay(10);
    }
  });
  printf("Started angle changer task\n");
}

void roller() {
  rollerIntake.move_relative(300, 600);
  // block until the roller intake is done
  while (rollerIntake.get_actual_velocity() != 0) {
    pros::delay(10);
  }
}

void skillsroller() {
  rollerIntake.move_relative(300, 600);
  // block until the roller intake is done
  while (rollerIntake.get_actual_velocity() != 0) {
    pros::delay(10);
  }
}

void on_roller() {
  flywheelPIDTask();
  flywheelTask();
  indexerTask();
  angleChangerTask();

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  roller();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  /* chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  roller();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-15, TURN_SPEED);
  chassis.wait_drive();

  angleChangerToggle = true;
  flywheelToggle = true;
  indexerToggle = true;

  pros::delay(3000);

  angleChangerToggle = false;
  flywheelToggle = false;
  indexerToggle = false; */

}

void off_roller() {
  flywheelPIDTask();
  flywheelTask();
  indexerTask();
  angleChangerTask();

  /* chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(15, TURN_SPEED);
  chassis.wait_drive();

  angleChangerToggle = true;
  flywheelToggle = true;
  indexerToggle = true;

  pros::delay(6000);

  angleChangerToggle = false;
  flywheelToggle = false;
  indexerToggle = false;

  chassis.set_turn_pid(-15, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  roller();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive(); */

}

void double_roller() {

  flywheelPIDTask();
  flywheelTask();
  indexerTask();
  angleChangerTask();

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  roller();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(50, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  roller();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

}

void skills() {
  flywheelPIDTask();
  flywheelTask();
  indexerTask();
  angleChangerTask();
  // TODO: add skills code here

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

