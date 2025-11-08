#pragma once

#include <Arduino.h>
#include "pins.hpp"

class LineSensor {
    public:
        static LineSensor& get_instance() {
            static LineSensor instance;
            return instance;
        }
        
        void loop();
        int* get_sensor_values();

    private:
        LineSensor();

        int last_sensor_values_[6];

        void update_sensor_values();
};
