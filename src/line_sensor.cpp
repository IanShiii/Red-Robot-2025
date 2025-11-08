#include "line_sensor.hpp"

LineSensor::LineSensor() {
    for (int i = 0; i < 6; i++) {
        last_sensor_values_[i] = 0;
    }
}

void LineSensor::loop() {
    update_sensor_values();
}

int* LineSensor::get_sensor_values() {
    return last_sensor_values_;
}

void LineSensor::update_sensor_values() {
    for (int i = 0; i < 6; ++i) {
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
    for (int i = 0; i < 6; ++i) {
        Serial.print(last_sensor_values_[i]);
        if (i < 5) {
            Serial.print(", ");
        }
    }
    Serial.println();
}
