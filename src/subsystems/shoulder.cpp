#include "subsystems/shoulder.hpp"

Shoulder::Shoulder() {
    servo_.attach(SHOULDER_SERVO_PIN, 600, 2400);
}

void Shoulder::loop() {}
void Shoulder::log() {}

void Shoulder::ready_pickup() {
    set_angle_degrees(SHOULDER_READY_PICKUP_ANGLE);
}

void Shoulder::active_pickup() {
    set_angle_degrees(SHOULDER_ACTIVE_PICKUP_ANGLE);
}

void Shoulder::set_angle_degrees(int angle) {
    servo_.write(angle);
}
