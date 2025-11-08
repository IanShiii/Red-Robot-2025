#include "subsystems/ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

void UltrasonicSensor::loop() {
    // To get a distance reading, we send a short pulse to the TRIG pin.

    // 1. Ensure the trigger pin is low
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);

    // 2. Send a 10 microsecond high pulse
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    // 3. Read the echo pin. pulseIn() measures the time (in microseconds)
    //    that the pin is HIGH.
    long duration_us = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);

    // 4. Calculate the distance in inches.
    //    Speed of sound is ~1130 ft/s, which is ~74 us/inch.
    //    The pulse travels to the object and back, so we divide by 2.
    last_distance_in_ = duration_us / 74.0 / 2.0;
}

double UltrasonicSensor::get_distance_in() {
    return last_distance_in_;
}

void UltrasonicSensor::log() {
    Serial.print("Sonar Distance: ");
    Serial.print(get_distance_in());
    Serial.println(" in");
}