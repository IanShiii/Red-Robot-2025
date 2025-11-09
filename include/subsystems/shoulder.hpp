#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

enum ShoulderState {
    READY_PICKUP,
    ACTIVE_PICKUP
};
class Shoulder : public Subsystem {
    public:
        static Shoulder& get_instance() {
            static Shoulder instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void set_state(ShoulderState state);
        ShoulderState get_state();

    private:
        friend class Subsystem;
        Shoulder();

        void set_angle_based_on_state();
        void set_angle_degrees(int angle);

        ShoulderState state_;
        Servo servo_;

};
