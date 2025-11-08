#pragma once

#include <Arduino.h>
#include "pins.hpp"
#include "settings.hpp"

class Drivetrain {
    public:
        Drivetrain();

        /**
         * @param left_y [-1, 1] positive means forward
         * @param right_x [-1, 1] positive means CCW
         */
        void set_speed_based_on_joysticks(double left_y, double right_x);

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
};
