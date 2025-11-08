#pragma once

#include <Arduino.h>

class Drivetrain {
    public:
        Drivetrain(uint8_t left_enable_pin, uint8_t right_enable_pin, uint8_t left_phase_pin, uint8_t right_phase_pin);

        /**
         * @param linear [-1, 1] positive means forward
         * @param angular [-1, 1] positive means CCW
         */
        void set_speed(double linear, double angular);

    private:
        /**
         * @param speed [-1, 1] Speed of left wheel, positive means it is pushing the robot forward
         */
        void set_left_speed(double speed);

        /**
         * @param speed [-1, 1] Speed of right wheel, positive means it is pushing the robot forward
         */
        void set_right_speed(double speed);

        uint8_t left_enable_pin_;
        uint8_t left_phase_pin_;
        uint8_t right_enable_pin_;
        uint8_t right_phase_pin_;
};
