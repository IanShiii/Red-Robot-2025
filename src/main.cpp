#include <Arduino.h>
#include "pins.hpp"
#include "drivetrain.hpp"
#include "controller.hpp"
#include "line_sensor.hpp"
#include "auton.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
LineSensor* line_sensor;

MoveStraightAuton auton;

bool auton_has_ran = false;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  line_sensor = &LineSensor::get_instance();
  Serial.begin(115200);
}

void loop() {
  controller->loop();
  line_sensor->loop();

  if (controller->is_B_pressed() && !auton_has_ran) {
    mode = AUTONOMOUS;
    auton.init();
  }

  if (mode == TELEOP) {
    drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());
  }

  if (mode == AUTONOMOUS) {
    AutonStatus autonStatus = auton.loop();
    if (autonStatus == DONE) {
      mode = TELEOP;
      auton_has_ran = true;
    }
  }
  
  delay(20);
}
