#include <Arduino.h>
#include "pins.hpp"
#include "settings.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/elevator.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
Elevator* elevator;

bool auton_has_ran = false;
double auton_start_time;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  elevator = &Elevator::get_instance();
  
  Serial.begin(115200);
}

void update_subsystems() {
  controller->loop();
  drivetrain->loop();
  elevator->loop();
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
  if (ELEVATOR_LOGGING_ENABLED) elevator->log();
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
    
    if (controller->is_Y_pressed()) {
      elevator->set_speed(0.5); // Raise elevator
    } else if (controller->is_A_pressed()) {
      elevator->set_speed(-0.5); // Lower elevator
    } else {
      elevator->set_speed(0.0); // Stop elevator
    }
  }

  if (mode == AUTONOMOUS) {
    double elapsed = (millis() - auton_start_time) / 1000.0;

#if LINE_SENSOR_ENABLED && DRIVETRAIN_ENABLED
    if (elapsed < 3.0) { // Run autonomous for 3 seconds
      drivetrain->set_speed(0.5, 0.0);
    } else {
      drivetrain->set_speed(0.0, 0.0);
      mode = TELEOP;
      auton_has_ran = true;
    }
#endif
  }
  
  delay(20);
}
