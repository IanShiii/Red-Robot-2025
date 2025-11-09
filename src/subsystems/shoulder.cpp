#include "subsystems/shoulder.hpp"

Shoulder::Shoulder() {
    servo_.attach(SHOULDER_SERVO_PIN, 600, 2400);
    state_ = READY_PICKUP;
    set_angle_based_on_state();
}

void Shoulder::loop() {}
void Shoulder::log() {}

void Shoulder::set_state(ShoulderState state) {
    state_ = state;
    set_angle_based_on_state();
}

Shoulder::ShoulderState Shoulder::get_state() {
    return state_;
}

void Shoulder::set_angle_based_on_state() {
    switch (state_) {
        case READY_PICKUP:
            set_angle_degrees(SHOULDER_READY_PICKUP_ANGLE);
            break;
        case ACTIVE_PICKUP:
            set_angle_degrees(SHOULDER_ACTIVE_PICKUP_ANGLE);
            break;
    }
}

void Shoulder::set_angle_degrees(int angle) {
    servo_.write(angle);
}
