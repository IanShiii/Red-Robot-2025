#include "commands.hpp"

void commands::follow_line() {
    LineSensor& line_sensor = LineSensor::get_instance();
    if (line_sensor.is_black_line_detected_on_left()) {
        Drivetrain::get_instance().set_speed(LINE_FOLLOWING_LINEAR_SPEED, LINE_FOLLOWING_ANGULAR_SPEED);
    } else if (line_sensor.is_black_line_detected_on_right()) {
        Drivetrain::get_instance().set_speed(LINE_FOLLOWING_LINEAR_SPEED, -LINE_FOLLOWING_ANGULAR_SPEED);
    } else {
        Drivetrain::get_instance().set_speed(LINE_FOLLOWING_LINEAR_SPEED, 0.0);
    }
}
