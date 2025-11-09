#include "subsystems/pusher.hpp"

Pusher::Pusher() {
    servo_.attach(PUSHER_SERVO_PIN, 600, 2400);
}

void Pusher::loop() {}
void Pusher::log() {}

void Pusher::retract() {
    set_angle_degrees(PUSHER_RETRACTED_ANGLE);
}

void Pusher::extend() {
    set_angle_degrees(PUSHER_EXTENDED_ANGLE);
}

void Pusher::set_angle_degrees(int angle) {
    servo_.write(angle);
}
