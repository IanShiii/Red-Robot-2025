#include "subsystems/line_sensor.hpp"

LineSensor::LineSensor() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        last_sensor_values_[i] = 0;
    }
}

double LineSensor::get_line_position() {
    double weighted_sum = 0;
    double total_value = 0;

    for (int i = 0; i < NUM_SENSORS; ++i) {
        // Invert the value so that 0 means dark and 3000 means bright
        double value = (3000 - last_sensor_values_[i]);
        // Center the weights around 0. Left sensors have negative weights, right sensors have positive weights
        // For 8 sensors, weights are: -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5
        double weight = i - (NUM_SENSORS - 1) / 2.0;
        weighted_sum += value * weight;
        total_value += value;
    }

    if (total_value == 0) return 0; // Avoid division by zero if all sensors are dark

    // Normalize to [-1, 1]
    return weighted_sum / total_value / ((NUM_SENSORS - 1) / 2.0);
}

void LineSensor::loop() {
    update_sensor_values();
}

void LineSensor::update_sensor_values() {
    for (int i = 0; i < NUM_SENSORS; ++i) {
        pinMode(LINE_SENSOR_PINS[i], OUTPUT);
        digitalWrite(LINE_SENSOR_PINS[i], HIGH);
        delay(1);
        pinMode(LINE_SENSOR_PINS[i], INPUT);
        unsigned long long start = micros();
        while (digitalRead(LINE_SENSOR_PINS[i]) && micros() - start < 10000) {}
        unsigned long long end = micros();

        int diff = end - start;

        last_sensor_values_[i] = diff;
    }
}

void LineSensor::log() {
    Serial.print("Line Sensor Values: ");
    for (int i = 0; i < NUM_SENSORS; ++i) {
        Serial.print(last_sensor_values_[i]);
        if (i < NUM_SENSORS - 1) {
            Serial.print(", ");
        }
    }
    Serial.println();
}
