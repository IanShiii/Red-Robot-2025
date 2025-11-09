#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Wrist : public Subsystem {
    public:
        static Wrist& get_instance() {
            static Wrist instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void ready_pickup();
        void active_pickup();

    private:
        friend class Subsystem;
        Wrist();
        
        void set_angle_degrees(int angle);

        Servo servo_;

};
