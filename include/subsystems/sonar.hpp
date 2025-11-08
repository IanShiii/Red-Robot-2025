#pragma once

#include <Arduino.h>
#include <Ultrasonic.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Sonar : public Subsystem {
    public:
        static Sonar& get_instance() {
            static Sonar instance;
            return instance;
        }

        void loop() override;
        void log() override;

        double get_distance_inches();

    private:
        friend class Subsystem;
        Sonar();

        Ultrasonic sonar_;
};
