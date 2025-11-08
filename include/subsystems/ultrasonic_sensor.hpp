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

        // State machine variables for non-blocking reads
        unsigned long last_ping_time_ms_ = 0;
        static constexpr unsigned int PING_INTERVAL_MS = 50; // Only ping every 50ms
        static constexpr unsigned long SENSOR_TIMEOUT_US = 15000; // Timeout for pulseIn, ~8ft
};
