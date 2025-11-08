#pragma once

#include <Arduino.h>
#include "subsystem.hpp"
#include "pins.hpp"

class UltrasonicSensor : public Subsystem {
    public:
        static UltrasonicSensor& get_instance() {
            static UltrasonicSensor instance;
            return instance;
        }

        void loop() override;
        void log() override;

        /**
         * @return The last measured distance to an object in inches.
         */
        double get_distance_in();

    private:
        friend class Subsystem;
        UltrasonicSensor();

        double last_distance_in_ = 0.0;
};
