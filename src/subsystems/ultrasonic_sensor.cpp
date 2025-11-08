#include "subsystems/ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

void UltrasonicSensor::loop() {
    // To get a distance reading, we send a short pulse to the TRIG pin.
    // This is a non-blocking approach. We only trigger a sensor reading
    // at a fixed interval, preventing it from hogging the CPU.
    if (millis() - last_ping_time_ms_ < PING_INTERVAL_MS) {
        return; // Not time to ping yet
    }

    last_ping_time_ms_ = millis();

    // 1. Send a 10 microsecond high pulse to the TRIG pin to start measurement.
    //    (Ensuring it's low first is good practice).
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    // 2. Read the echo pin. pulseIn() is still blocking, but now we've added
    //    a reasonable timeout and we only call it occasionally.
    long duration_us = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, SENSOR_TIMEOUT_US);

    // 3. Calculate the distance only if a valid pulse was received.
    //    If pulseIn() times out, it returns 0. We should ignore this,
    //    as it means "out of range", not "distance is zero".
    if (duration_us > 0) {
        // Speed of sound is ~1130 ft/s, which is ~74 us/inch.
        // The pulse travels to the object and back, so we divide by 2.
        last_distance_in_ = duration_us / 74.0 / 2.0;
    }
}

double UltrasonicSensor::get_distance_in() {
    return last_distance_in_;
}

void UltrasonicSensor::log() {
    Serial.print("Sonar Distance: ");
    Serial.print(get_distance_in());
    Serial.println(" in");
}