#include "tasks.hpp"

void flywheelTask() {
  printf("Starting flywheel task\n");
  pros::Task flywheelTask([]() {
      while (true) {
          if (flywheelToggle) {
              flywheelMotor.move_velocity(600);
          } else {
              flywheelMotor.move_velocity(0);
          }
          pros::delay(10);
      }
  });
  printf("Started flywheel task\n");
}

void flywheelPIDTask() {
  printf("Starting flywheel PID task\n");
  pros::Task flywheelPIDTask([]() {
    while (true) {
      if (flywheelToggle) {
        flywheelPID(flywheelkP, flywheelkI, flywheelkD, flywheelIntegralLimit);
      }
    }
  });
  printf("Started flywheel PID task\n");
}

void indexerTask() {
  printf("Starting indexer task\n");
  pros::Task indexerTask([]() {
    while (true) {
      if (rollerIndexerToggle) {
        printf("Indexer on\n");
        rollerIntakeMotor.move_velocity(600);
      } else {
        printf("Indexer off\n");
        rollerIntakeMotor.move_velocity(0);
      }
      pros::delay(10);
    }
  });
  printf("Started indexer task\n");
}

void setupTasks() {
  flywheelTask();
  flywheelPIDTask();
  indexerTask();
}