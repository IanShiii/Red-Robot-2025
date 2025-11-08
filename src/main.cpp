#include <Arduino.h>
#include "pins.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/line_sensor.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
LineSensor* line_sensor;

bool auton_has_ran = false;

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
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (LINE_SENSOR_LOGGING_ENABLED) line_sensor->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
}

void loop() {
  update_subsystems();
  log_subsystems();

  // if (controller->is_B_pressed() && !auton_has_ran) {
  //   mode = AUTONOMOUS;
  //   auton.init();
  // }

  if (mode == TELEOP) {
    drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());
  }

  // if (mode == AUTONOMOUS) {
  //   CommandStatus autonStatus = auton.loop();
  //   if (autonStatus == DONE) {
  //     mode = TELEOP;
  //     auton_has_ran = true;
  //   }
  // }
  
  delay(20);
}
