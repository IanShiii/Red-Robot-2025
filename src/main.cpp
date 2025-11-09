#include <Arduino.h>
#include "pins.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/controller.hpp"
#include "subsystems/line_sensor.hpp"
#include "subsystems/elevator.hpp"
#include "subsystems/gate.hpp"
#include "subsystems/ultrasonic_sensor.hpp"
#include "commands.hpp"

enum Mode {AUTONOMOUS, TELEOP};

Mode mode = TELEOP;

Drivetrain* drivetrain;
Controller* controller;
LineSensor* line_sensor;
Elevator* elevator;
Gate* gate;
// UltrasonicSensor* ultrasonic_sensor;

bool auton_has_ran = false;
double auton_start_time;

void setup() {
  drivetrain = &Drivetrain::get_instance();
  controller = &Controller::get_instance();
  line_sensor = &LineSensor::get_instance();
  elevator = &Elevator::get_instance();
  gate = &Gate::get_instance();
  // ultrasonic_sensor = &UltrasonicSensor::get_instance();

  Serial.begin(115200);
}

void update_subsystems() {
  controller->loop();
  line_sensor->loop();
  drivetrain->loop();
  elevator->loop();
  gate->loop();
  // ultrasonic_sensor->loop();
}

void log_subsystems() {
  if (CONTROLLER_LOGGING_ENABLED) controller->log();
  if (LINE_SENSOR_LOGGING_ENABLED) line_sensor->log();
  if (DRIVETRAIN_LOGGING_ENABLED) drivetrain->log();
  if (ELEVATOR_LOGGING_ENABLED) elevator->log();
  if (GATE_LOGGING_ENABLED) gate->log();
  // if (SONAR_LOGGING_ENABLED) ultrasonic_sensor->log();
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
    // Standard tele-operated driving
    drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());
    
    // Elevator controls using the shoulder buttons
    if (controller->is_RB_pressed()) {
      elevator->set_speed(1.0); // Raise elevator
    } else if (controller->is_LB_pressed()) {
      elevator->set_speed(-1.0); // Lower elevator
    } else {
      elevator->set_speed(0.0); // Stop elevator if no buttons are pressed
    }
  }
  
  if (mode == AUTONOMOUS) {
    double elapsed = (millis() - auton_start_time) / 1000.0;
    
    if (elapsed < 3.0) { // Run autonomous for 3 seconds
      commands::follow_line();
    } else {
      mode = TELEOP;
      auton_has_ran = true;
    }
  }
  
  delay(20);
}
