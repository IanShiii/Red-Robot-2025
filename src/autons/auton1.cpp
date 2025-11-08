#include "auton.hpp"

Auton1::Auton1() {}

void Auton1::init() {
    start_time_milliseconds_ = millis();
}

AutonStatus Auton1::loop() {
    unsigned long elapsed_time = millis() - start_time_milliseconds_;
    if (elapsed_time >= AUTON_DURATION_MILLISECONDS) {
        on_exit();
        return DONE;
    }
    return IN_PROGRESS;
}

void Auton1::on_exit() {}
