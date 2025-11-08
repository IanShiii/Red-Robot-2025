#include "subsystems/sonar.hpp"

Sonar::Sonar() : sonar_(ULTRASONIC_TRIG, ULTRASONIC_ECHO) {}

void Sonar::loop() {}
void Sonar::log() {
    Serial.println("Sonar: " + String(get_distance_inches()) + " inches");
}

double Sonar::get_distance_inches() {
    return sonar_.read(INC);
}
