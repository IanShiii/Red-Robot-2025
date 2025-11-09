#include "subsystems/wrist.hpp"

Wrist::Wrist() {
    servo_.attach(WRIST_SERVO_PIN, 600, 2400);
}

void Wrist::loop() {}
void Wrist::log() {}

void Wrist::ready_pickup() {
    set_angle_degrees(WRIST_READY_PICKUP_ANGLE);
}

void Wrist::active_pickup() {
    set_angle_degrees(WRIST_ACTIVE_PICKUP_ANGLE);
}

void Wrist::set_angle_degrees(int angle) {
    servo_.write(angle);
}
