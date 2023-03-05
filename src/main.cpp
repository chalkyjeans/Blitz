#include "main.h"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "tasks.hpp"
#include "drivercontrol.hpp"
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

pros::Motor rollerIntakeMotor(21, MOTOR_GEARSET_06, true);
pros::Motor flywheelMotor(11, MOTOR_GEARSET_06, true);

pros::ADIDigitalOut expansion('G');

bool flywheelToggle = false;
bool rollerIndexerToggle = false;
bool boost = false;

double flywheelkP = 0.5;
double flywheelkI = 0.0001;
double flywheelkD = 0.1;
double flywheelIntegralLimit = 10;

Drive chassis(
  {-14, -15, 13},
  {20, 16, -8},
  9,
  3.25,
  600,
  0.6
);

pros::Motor left1(14, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left2(15, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left3(13, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right1(20, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right2(16, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right3(8, pros::E_MOTOR_GEARSET_06, true);

pros::MotorGroup leftMotors({left1, left2, left3});
pros::MotorGroup rightMotors({right1, right2, right3});

void initialize() { 

  sylib::initialize();
  printf("Sylib initialized\n");
  
  pros::delay(500);

  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0);
  chassis.set_curve_default(0, 0);
  default_constants();
  exit_condition_defaults();

  pros::screen::erase();

  chassis.initialize();
  printf("Chassis initialized\n");

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

  // setupTasks();

  // indexer_test();
  // turn_test();
  // drive_test();
  // on_roller();
  // off_roller();
  skills();
  // double_roller();

}

void opcontrol() {
  
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  /* std::shared_ptr<graphy::AsyncGrapher> grapher(new graphy::AsyncGrapher("Flywheel Velocity vs Time"));
  grapher -> addDataType("Desired Value", COLOR_RED);
  grapher -> addDataType("Actual Value", COLOR_BLUE);
  grapher -> startTask(); */

  while (true) {

    // grapher -> update("Desired Value", flywheelMotor.get_target_velocity());
    // grapher -> update("Actual Value", flywheelMotor.get_actual_velocity());

    pros::Task rollerIntakeTask(rollerIntake);
    pros::Task flywheelTask(flywheel);
    pros::Task expansionTask(expansionToggle);

    pros::delay(ez::util::DELAY_TIME);

  }
  
}
