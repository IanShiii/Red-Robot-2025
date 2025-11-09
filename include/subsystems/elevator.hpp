#pragma once

#include <Arduino.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Elevator : public Subsystem {
    public:
        static Elevator& get_instance() {
            static Elevator instance;
            return instance;
        }

        void loop() override;
        void log() override;

        // This method is public to allow control from main.cpp or commands.
        /**
         * @param speed [-1, 1] negative means going down, positive means going up
         */
        void set_speed(double speed);

    private:
        // The constructor is private to enforce the singleton pattern.
        friend class Subsystem;
        Elevator();
};
