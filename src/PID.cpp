#include "PID.hpp"
#include "autons.hpp"

int integral = 0;
int prevError = 0;

void flywheelPID(double kP, double kI, double kD, double integralLimit) {

  int targetRPM = flywheelMotor.get_target_velocity();
  int actualRPM = flywheelMotor.get_actual_velocity();
  int error = targetRPM - actualRPM;

  integral = integral + error;

  if (error == 0) {
    integral = 0;
  }

  if (abs(error) > integralLimit) {
    integral = 0;
  }

  int derivative = error - prevError;
  prevError = error;

  int RPM = (kP * error) + (kI * integral) * (kD * derivative);

  flywheelMotor.move_velocity(RPM);

  pros::delay(10);

}
