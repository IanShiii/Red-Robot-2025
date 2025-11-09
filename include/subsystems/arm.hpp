#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

enum ArmState {
    STOW,
    READY_PICKUP,
    ACTIVE_PICKUP,
    LEVEL_3_READY,
    LEVEL_3_SCORE,
    LEVEL_2_READY,
    LEVEL_2_SCORE,
    LEVEL_1_READY,
    LEVEL_1_SCORE
};

class Arm : public Subsystem {
    public:
        static Arm& get_instance() {
            static Arm instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void set_state(ArmState state);
        ArmState get_state();

    private:
        friend class Subsystem;
        Arm();

        void set_angles_based_on_state();
        void set_angles_degrees(int shoulder_angle, int wrist_angle);

        ArmState state_;
        Servo shoulder_servo_;
        Servo wrist_servo_;
};
