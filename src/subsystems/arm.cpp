#include "subsystems/arm.hpp"

Arm::Arm() {
    wrist_servo_.attach(WRIST_SERVO_PIN, 600, 2400);
    shoulder_servo_.attach(SHOULDER_SERVO_PIN, 600, 2400);
    state_ = READY_PICKUP;
    set_angles_based_on_state();
}

void Arm::loop() {}
void Arm::log() {}

void Arm::set_state(ArmState state) {
    state_ = state;
    set_angles_based_on_state();
}

ArmState Arm::get_state() {
    return state_;
}

void Arm::set_angles_based_on_state() {
    switch (state_) {
        case STOW:
            set_angles_degrees(SHOULDER_STOW_ANGLE, WRIST_STOW_ANGLE);
            break;
        case READY_PICKUP:
            set_angles_degrees(SHOULDER_READY_PICKUP_ANGLE, WRIST_READY_PICKUP_ANGLE);
            break;
        case ACTIVE_PICKUP:
            set_angles_degrees(SHOULDER_ACTIVE_PICKUP_ANGLE, WRIST_ACTIVE_PICKUP_ANGLE);
            break;
        case LEVEL_3_READY:
            set_angles_degrees(SHOULDER_LEVEL_3_READY_ANGLE, WRIST_LEVEL_3_READY_ANGLE);
            break;
        case LEVEL_3_SCORE:
            set_angles_degrees(SHOULDER_LEVEL_3_SCORE_ANGLE, WRIST_LEVEL_3_SCORE_ANGLE);
            break;
        case LEVEL_2_READY:
            set_angles_degrees(SHOULDER_LEVEL_2_READY_ANGLE, WRIST_LEVEL_2_READY_ANGLE);
            break;
        case LEVEL_2_SCORE:
            set_angles_degrees(SHOULDER_LEVEL_2_SCORE_ANGLE, WRIST_LEVEL_2_SCORE_ANGLE);
            break;
        case LEVEL_1_READY:
            set_angles_degrees(SHOULDER_LEVEL_1_READY_ANGLE, WRIST_LEVEL_1_READY_ANGLE);
            break;
        case LEVEL_1_SCORE:
            set_angles_degrees(SHOULDER_LEVEL_1_SCORE_ANGLE, WRIST_LEVEL_1_SCORE_ANGLE);
            break;
    }
}

void Arm::set_angles_degrees(int shoulder_angle, int wrist_angle) {
    shoulder_servo_.write(shoulder_angle);
    wrist_servo_.write(wrist_angle);
}
