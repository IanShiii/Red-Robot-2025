#include "subsystems/elevator.hpp"

Elevator::Elevator() {
    pinMode(ELEVATOR_ENABLE_PIN, OUTPUT);
    pinMode(ELEVATOR_PHASE_PIN, OUTPUT);
}

void Elevator::loop() {}
void Elevator::log() {}

void Elevator::set_speed(double speed) {
    speed += ELEVATOR_kG;
    speed = constrain(speed, -1.0, 1.0);
    analogWrite(ELEVATOR_ENABLE_PIN, int(255 * abs(speed)));
    digitalWrite(ELEVATOR_PHASE_PIN, speed > 0.0 ? HIGH : LOW);
}
