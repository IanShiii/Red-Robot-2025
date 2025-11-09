#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

enum WristState {
    READY_PICKUP,
    ACTIVE_PICKUP
};
class Wrist : public Subsystem {
    public:
        static Wrist& get_instance() {
            static Wrist instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void set_state(WristState state);
        WristState get_state();

    private:
        friend class Subsystem;
        Wrist();
        
        void set_angle_based_on_state();
        void set_angle_degrees(int angle);

        WristState state_;
        Servo servo_;

};
