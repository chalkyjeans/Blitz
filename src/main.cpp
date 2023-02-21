#include "main.h"
#include "autons.hpp"
#include "PID.hpp"
#include "gif-pros/gifclass.hpp"
#include "pros/colors.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include "sylib/system.hpp"
#include "Graphy/Grapher.hpp"
#include <cstdio>
#include <memory>

int DRIVE_SPEED = 110;
int TURN_SPEED = 90;
int SWING_SPEET = 90;

pros::Motor rollerIntake(2, MOTOR_GEARSET_06, true);
pros::Motor flywheel(1, MOTOR_GEARSET_06, true);

pros::ADIDigitalOut angleChanger1(1);
pros::ADIDigitalOut angleChanger2(2);
pros::ADIDigitalOut expansion(8);

int flywheelRPM = 600;
bool flywheelToggle = false;
bool angleChangerToggle = false;
bool indexerToggle = false;

double flywheelkP = 0.5;
double flywheelkI = 0.0001;
double flywheelkD = 0.1;
double flywheelIntegralLimit = 10;

bool startedDriver = false;
int startTime;
bool endgame = false;

Drive chassis(
  {-13, -14, 15},
  {18, 19, -20},
  7,
  3.25,
  600,
  0.6
);

void initialize() {

  ez::print_ez_template();
  
  pros::delay(500);

  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);
  default_constants();
  exit_condition_defaults();

  chassis.initialize();
  printf("Chassis initialized\n");

  sylib::initialize();
  printf("Sylib initialized\n");

  pros::screen::erase();

  if (ez::util::IS_SD_CARD) {
    printf("SD card detected - Loading gif\n");
    static Gif gif("/usd/tempest-compressed.gif", lv_scr_act());
    printf("Loaded gif\n");
  } else {
    printf("No SD card detected\n");
  }

}

void disabled() {
  // . . .
}


void competition_initialize() {
  // . . .
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  // on_roller();
  // off_roller();
  // skills();
  // double_roller();

}

void opcontrol() {
  
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  if (!startedDriver) {
    startTime = pros::millis();
  }
  startedDriver = true;

  /* std::shared_ptr<graphy::AsyncGrapher> grapher(new graphy::AsyncGrapher("Flywheel Velocity vs Time"));
  grapher -> addDataType("Desired Value", COLOR_RED);
  grapher -> addDataType("Actual Value", COLOR_BLUE);
  grapher -> startTask(); */

  while (true) {

    // grapher -> update("Desired Value", flywheel.get_target_velocity());
    // grapher -> update("Actual Value", flywheel.get_actual_velocity());

    if (pros::millis() - startTime > 95000) {
      endgame = true;
    }

    if (master.get_digital_new_press(DIGITAL_X)) {
      if (endgame) {
        expansion.set_value(true);
      }
    }

    pros::Task flywheelTask([]() {
      flywheelPID(flywheelkP, flywheelkI, flywheelkD, flywheelIntegralLimit);
    }, "flywheelTask");

    chassis.tank();
    // chassis.arcade_standard(ez::SPLIT);

    if (master.get_digital(DIGITAL_L1)) {
      rollerIntake.move_velocity(600);
    } else if (master.get_digital(DIGITAL_L2)) {
      rollerIntake.move_velocity(-600);
    } else {
      rollerIntake.move_velocity(0);
    }

    if (master.get_digital_new_press(DIGITAL_A)) {
      flywheelToggle = !flywheelToggle;
    }

    if (flywheelToggle) {
      flywheel.move_velocity(flywheelRPM);
    } else {
      flywheel.move_velocity(0);
    }

    if (master.get_digital_new_press(DIGITAL_R2)) {
      angleChangerToggle = !angleChangerToggle;
    }

    if (angleChangerToggle) { // angle changer up
      printf("Angle changer up\n");
      angleChanger1.set_value(true);
      angleChanger2.set_value(true);
      flywheelRPM = 450;
    } else { // angle changer down
      printf("Angle changer down\n");
      angleChanger1.set_value(false);
      angleChanger2.set_value(false);
      flywheelRPM = 600;
    }

    pros::delay(ez::util::DELAY_TIME);

  }

}
