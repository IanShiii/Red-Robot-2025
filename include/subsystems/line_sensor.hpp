#pragma once

#include <Arduino.h>
#include "subsystem.hpp"
#include "settings.hpp"
#include "pins.hpp"

class LineSensor : public Subsystem {
    public:
        static LineSensor& get_instance() {
            static LineSensor instance;
            return instance;
        }
        
        void loop() override;
        void log() override;
        /**
         * @return A position from [-1, 1] where -1 means the line is at the far left, and 1 means the line is at the far right of the robot
         */
        double get_line_position();

    private:
        friend class Subsystem;
        LineSensor();

        static constexpr int NUM_SENSORS = 8;

        // Each value is in the range [0, 3000]
        // 0 means the sensor is on a very bright surface, and 3000 means the sensor is on a dark surface
        int last_sensor_values_[NUM_SENSORS];

        void update_sensor_values();
};
