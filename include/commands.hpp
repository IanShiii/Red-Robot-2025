#pragma once

#include "subsystems/line_sensor.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/elevator.hpp"
#include "subsystems/gate.hpp"
#include "subsystems/ultrasonic_sensor.hpp"
#include "subsystems/controller.hpp"

void follow_line() {
    double line_position = LineSensor::get_instance().get_line_position();
    double linear_speed = LINE_FOLLOWING_LINEAR_SPEED;
    double angular_speed = line_position * LINE_FOLLOWING_ANGULAR_MULTIPLIER;
    Drivetrain::get_instance().set_speed(linear_speed, angular_speed);
}
