#include "auton.hpp"

MoveStraightAuton::MoveStraightAuton() {}

void MoveStraightAuton::init() {
    start_time_milliseconds_ = millis();
}

CommandStatus MoveStraightAuton::loop() {
    unsigned long elapsed_time = millis() - start_time_milliseconds_;
    
    if (elapsed_time >= DURATION_MILLISECONDS || elapsed_time >= MAX_AUTON_DURATION_MILLISECONDS) {
        on_exit();
        return DONE;
    }

    Drivetrain::get_instance().set_speed(0.5, 0.0);

    return IN_PROGRESS;
}

void MoveStraightAuton::on_exit() {
    Drivetrain::get_instance().set_speed(0.0, 0.0);
}
