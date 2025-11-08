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

    private:
        friend class Subsystem;
        Elevator();

        /**
         * @param speed [-1, 1] negative means going down, positive means going up
         */
        void set_speed(double speed);
};
