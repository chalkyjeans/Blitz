#include "main.h"
#include "autons.hpp"
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

pros::Motor rollerIntakeMotor(1, MOTOR_GEARSET_06, true);
pros::Motor flywheelMotor(2, MOTOR_GEARSET_06, true);

pros::ADIDigitalOut expansion(8);

bool flywheelToggle = false;
bool indexerToggle = false;

double flywheelkP = 0.5;
double flywheelkI = 0.0001;
double flywheelkD = 0.1;
double flywheelIntegralLimit = 10;

Drive chassis(
  {-13, -14, 15},
  {18, 19, -20},
  16,
  3.25,
  600,
  0.6
);

void initialize() { 

  sylib::initialize();
  printf("Sylib initialized\n");

  ez::print_ez_template();
  
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

  setupTasks();

  test();
  // on_roller();
  // off_roller();
  // skills();
  // double_roller();

}

void opcontrol() {
  
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  /* std::shared_ptr<graphy::AsyncGrapher> grapher(new graphy::AsyncGrapher("Flywheel Velocity vs Time"));
  grapher -> addDataType("Desired Value", COLOR_RED);
  grapher -> addDataType("Actual Value", COLOR_BLUE);
  grapher -> startTask(); */

  while (true) {

    // grapher -> update("Desired Value", flywheel.get_target_velocity());
    // grapher -> update("Actual Value", flywheel.get_actual_velocity());

    chassis.tank();

    pros::Task rollerIntakeTask(rollerIntake);
    pros::Task flywheelTask(flywheel);
    pros::Task expansionTask(expansionToggle);

    pros::delay(ez::util::DELAY_TIME);

  }

}
