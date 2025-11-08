#include "subsystems/line_sensor.hpp"

LineSensor::LineSensor() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        last_sensor_values_[i] = 0;
    }
}

void LineSensor::loop() {
    update_sensor_values();
}

void LineSensor::log() {
    Serial.print("Line Sensor Values: ");
    for (int i = 0; i < NUM_SENSORS; ++i) {
        Serial.print(last_sensor_values_[i]);
        if (i < NUM_SENSORS - 1) {
            Serial.print(", ");
        }
    }
    Serial.print(" | Line Detected on Left: ");
    Serial.print(is_black_line_detected_on_left() ? "Yes" : "No");
    Serial.print(" | Line Detected on Right: ");
    Serial.print(is_black_line_detected_on_right() ? "Yes" : "No");
    Serial.println();
}

void LineSensor::update_sensor_values() {
    for (int i = 1; i < NUM_SENSORS; ++i) {
        pinMode(LINE_SENSOR_PINS[i], OUTPUT);
        digitalWrite(LINE_SENSOR_PINS[i], HIGH);
        delay(1);
        pinMode(LINE_SENSOR_PINS[i], INPUT);
        unsigned long long start = micros();
        while (digitalRead(LINE_SENSOR_PINS[i]) && micros() - start < SENSOR_READ_TIMEOUT_US) {}
        unsigned long long end = micros();

        int diff = end - start;

        last_sensor_values_[i] = diff;
    }
}

bool LineSensor::is_black_line_detected_on_left() {
    // If its detected on the right, return false
    for (int i = 3; i < NUM_SENSORS; ++i) {
        if (last_sensor_values_[i] < BLACK_THRESHOLD) { 
            return false;
        }
    }

    // If its detected on the left, return true
    for (int i = 1; i < 3; ++i) {
        if (last_sensor_values_[i] < BLACK_THRESHOLD) { 
            return true;
        }
    }

    return false;
}

bool LineSensor::is_black_line_detected_on_right() {
    // If its detected on the left, return false
    for (int i = 1; i < 3; ++i) {
        if (last_sensor_values_[i] < BLACK_THRESHOLD) { 
            return false;
        }
    }

    // If its detected on the right, return true
    for (int i = 3; i < NUM_SENSORS; ++i) {
        if (last_sensor_values_[i] < BLACK_THRESHOLD) { 
            return true;
        }
    }
    
    return false;
}
