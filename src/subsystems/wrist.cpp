#include "subsystems/wrist.hpp"

Wrist::Wrist() {
    servo_.attach(WRIST_SERVO_PIN, 600, 2400);
    state_ = READY_PICKUP;
    set_angle_based_on_state();
}

void Wrist::loop() {}
void Wrist::log() {}

void Wrist::set_state(WristState state) {
    state_ = state;
    set_angle_based_on_state();
}

Wrist::WristState Wrist::get_state() {
    return state_;
}

void Wrist::set_angle_based_on_state() {
    switch (state_) {
        case READY_PICKUP:
            set_angle_degrees(WRIST_READY_PICKUP_ANGLE);
            break;
        case ACTIVE_PICKUP:
            set_angle_degrees(WRIST_ACTIVE_PICKUP_ANGLE);
            break;
    }
}

void Wrist::set_angle_degrees(int angle) {
    servo_.write(angle);
}
