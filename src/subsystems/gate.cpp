#include "subsystems/gate.hpp"

Gate::Gate() {
    servo_.attach(GATE_SERVO_PIN, 600, 2400);
}

void Gate::loop() {}
void Gate::log() {}

void Gate::open() {
    set_angle_degrees(GATE_OPEN_ANGLE);
}

void Gate::close() {
    set_angle_degrees(GATE_CLOSE_ANGLE);
}

void Gate::set_angle_degrees(int angle) {
    servo_.write(angle);
}
