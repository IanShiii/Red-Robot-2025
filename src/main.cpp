#include <Arduino.h>
#include "pins.hpp"
#include "settings.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/shoulder.hpp"
#include "subsystems/wrist.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
Shoulder* shoulder;
Wrist* wrist;

bool auton_has_ran = false;
double auton_start_time;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  shoulder = &Shoulder::get_instance();
  wrist = &Wrist::get_instance();
  
  Serial.begin(115200);
}

void update_subsystems() {
  controller->loop();
  drivetrain->loop();
  shoulder->loop();
  wrist->loop();
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
  if (SHOULDER_LOGGING_ENABLED) shoulder->log();
  if (WRIST_LOGGING_ENABLED) wrist->log();
}

void loop() {
  update_subsystems();
  log_subsystems();
  
  // Press 'B' on the controller to start the one-time autonomous routine.
  if (controller->is_B_pressed() && !auton_has_ran) {
    mode = AUTONOMOUS;
    auton_start_time = millis();
  }

  if (mode == TELEOP) {
    drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());

    // RT extend the shoulder and wrist for pickup.
    // Releasing sends the shoulder and wrist back to the ready position.
    if (controller->is_RT_pressed()) {
      shoulder->set_state(ShoulderState::ACTIVE_PICKUP);
      wrist->set_state(WristState::ACTIVE_PICKUP);
    } else if (shoulder->get_state() == ShoulderState::ACTIVE_PICKUP) {
      shoulder->set_state(ShoulderState::READY_PICKUP);
      wrist->set_state(WristState::READY_PICKUP);
    }
  }

  if (mode == AUTONOMOUS) {
    double elapsed = (millis() - auton_start_time) / 1000.0;
    if (elapsed < 2) {
      drivetrain->set_speed(0.5, 0);
    } else {
      mode = TELEOP;
      auton_has_ran = true;
      drivetrain->set_speed(0, 0);
    }
  }
  delay(20);
}
