#include <Arduino.h>
#include "pins.hpp"
#include "drivetrain.hpp"
#include "controller.hpp"

Drivetrain *drivetrain = nullptr;
Controller *controller = nullptr;

void setup() {
  Serial.begin(115200);
  drivetrain = new Drivetrain();
  controller = new Controller();
}

void loop() {
  controller->loop();
  drivetrain->set_speed_based_on_joysticks(controller->get_left_y(), controller->get_right_x());
  
  delay(20);
}
