#include <Arduino.h>
#include "pins.hpp"
#include "settings.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/arm.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
Arm* arm;

bool auton_has_ran = false;
double auton_start_time;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  arm = &Arm::get_instance();
  Serial.begin(115200);
}

void update_subsystems() {
  controller->loop();
  drivetrain->loop();
  arm->loop();
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
  if (ARM_LOGGING_ENABLED) arm->log();
}

bool arm_is_in_ready_to_score_position() {
  return arm->get_state() == ArmState::LEVEL_3_READY ||
         arm->get_state() == ArmState::LEVEL_2_READY ||
         arm->get_state() == ArmState::LEVEL_1_READY;
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

    // RT is the pickup button
    // Releasing RT will return the arm to the ready position

    if (controller->is_RT_pressed()) {
      arm->set_state(ArmState::ACTIVE_PICKUP);
    } else if (arm->get_state() == ArmState::ACTIVE_PICKUP) {
      arm->set_state(ArmState::READY_PICKUP);
    }

    // Pressing LT will score the arm if it is in the ready to score position.
    // Releasing LT will return the arm to the corresponding ready position.
    if (controller->is_LT_pressed()) {
      if (arm_is_in_ready_to_score_position()) {
        switch (arm->get_state()) {
          case ArmState::LEVEL_3_READY:
            arm->set_state(ArmState::LEVEL_3_SCORE);
            break;
          case ArmState::LEVEL_2_READY:
            arm->set_state(ArmState::LEVEL_2_SCORE);
            break;
          case ArmState::LEVEL_1_READY:
            arm->set_state(ArmState::LEVEL_1_SCORE);
            break;
        }
      }
    } else {
      switch (arm->get_state()) {
        case ArmState::LEVEL_3_SCORE:
          arm->set_state(ArmState::LEVEL_3_READY);
          break;
        case ArmState::LEVEL_2_SCORE:
          arm->set_state(ArmState::LEVEL_2_READY);
          break;
        case ArmState::LEVEL_1_SCORE:
          arm->set_state(ArmState::LEVEL_1_READY);
          break;
        default:
          // Do nothing, the arm is not in a scoring state
          break;
      }
    }

    // Pressing Y, X, or A will move the arm to the corresponding level's ready position.
    if (controller->is_Y_pressed()) {
      arm->set_state(ArmState::LEVEL_3_READY);
    } else if (controller->is_X_pressed()) {
      arm->set_state(ArmState::LEVEL_2_READY);
    } else if (controller->is_A_pressed()) {
      arm->set_state(ArmState::LEVEL_1_READY);
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
