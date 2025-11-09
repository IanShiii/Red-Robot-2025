#pragma once

#include <Arduino.h>
#include <optional>
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
         * @return The last measured distance in inches, or std::nullopt if no valid reading is available.
         */
        std::optional<double> get_distance_in();

    private:
        friend class Subsystem;
        UltrasonicSensor();

        std::optional<double> last_distance_in_ = std::nullopt;

        // State machine variables for non-blocking reads
        unsigned long last_ping_time_ms_ = 0;
        static constexpr unsigned int PING_INTERVAL_MS = 50; // Only ping every 50ms
        static constexpr unsigned long SENSOR_TIMEOUT_US = 15000; // Timeout for pulseIn, ~8ft
};
