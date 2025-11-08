#include <Arduino.h>
#include "pins.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/elevator.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/line_sensor.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
Elevator* elevator;
LineSensor* line_sensor;

bool auton_has_ran = false;
double auton_start_time;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  line_sensor = &LineSensor::get_instance();

  Serial.begin(115200);
}

void update_subsystems() {
  controller->loop();
  line_sensor->loop();
  drivetrain->loop();
  elevator->loop();
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (LINE_SENSOR_LOGGING_ENABLED) line_sensor->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
  // if (ELEVATOR_LOGGING_ENABLED) elevator->log();
}

void loop() {
  update_subsystems();
  log_subsystems();

  if (controller->is_B_pressed() && !auton_has_ran) {
    mode = AUTONOMOUS;
    auton_start_time = millis();
  }

  if (mode == TELEOP) {
    drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());
  }

  if (mode == AUTONOMOUS) {
    double elapsed = (millis() - auton_start_time) / 1000.0;

    if (elapsed < 20.0) {
      // Proportional control for line following
      double line_position = line_sensor->get_line_position();
      double angular_speed = line_position * AUTON_LINE_FOLLOW_KP;
      drivetrain->set_speed(AUTON_LINE_FOLLOW_SPEED, angular_speed);
    } else {
      drivetrain->set_speed(0.0, 0.0); // Stop the robot
      mode = TELEOP;
      auton_has_ran = true;
    }
  }
  
  delay(20);
}
