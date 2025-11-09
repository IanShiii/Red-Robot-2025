#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Shoulder : public Subsystem {
    public:
        static Shoulder& get_instance() {
            static Shoulder instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void ready_pickup();
        void active_pickup();

    private:
        friend class Subsystem;
        Shoulder();
        
        void set_angle_degrees(int angle);

        Servo servo_;

};
