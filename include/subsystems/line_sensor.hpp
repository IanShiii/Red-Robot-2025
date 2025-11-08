#pragma once

#include <Arduino.h>
#include <optional>
#include "subsystem.hpp"
#include "pins.hpp"
#include "settings.hpp"

class LineSensor : public Subsystem {
    public:
        static LineSensor& get_instance() {
            static LineSensor instance;
            return instance;
        }
        
        void loop() override;
        void log() override;
        
        bool is_black_line_detected_on_left();
        bool is_black_line_detected_on_right();

    private:
        friend class Subsystem;
        LineSensor();

        static constexpr int NUM_SENSORS = 6;
        static constexpr int SENSOR_READ_TIMEOUT_US = 10000;

        // Each value is in the range [0, 10000]
        // 0 means the sensor is on a dark surface, and 10000 means the sensor is on a bright surface
        int last_sensor_values_[NUM_SENSORS];

        void update_sensor_values();
};
