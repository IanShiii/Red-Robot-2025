#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Pusher : public Subsystem {
    public:
        static Pusher& get_instance() {
            static Pusher instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void retract();
        void extend();
        void set_angle_degrees(int angle);

    private:
        friend class Subsystem;
        Pusher();

        Servo servo_;

};
