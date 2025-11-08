#pragma once

#include <Arduino.h>
#include "pins.hpp"

class LineSensor {
    public:
        static LineSensor& get_instance() {
            static LineSensor instance;
            return instance;
        }
        
        /**
         * Updates the sensor values. Should be called in the main loop.
         */
        void loop();

        int* get_sensor_values();

        /**
         * Sends any relevant information to the serial monitor for debugging
         */
        void log();

    private:
        LineSensor();

        int last_sensor_values_[6];

        void update_sensor_values();
};
