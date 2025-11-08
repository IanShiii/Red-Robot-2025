#pragma once

#include <Arduino.h>
#include "drivetrain.hpp"
#include "line_sensor.hpp"

#define MAX_AUTON_DURATION_MILLISECONDS 20000 // 20 seconds

enum AutonStatus {IN_PROGRESS, DONE};

template <typename T>
class Auton {
    public:
        virtual void init() = 0;
        virtual AutonStatus loop() = 0;

    protected:
        unsigned long start_time_milliseconds_;

        /**
         * Code to run when autonomous mode is exited
         */
        virtual void on_exit() = 0;
};

class MoveStraightAuton : public Auton<MoveStraightAuton> {
    double DURATION_MILLISECONDS = 10000; // 10 seconds

    public:
        MoveStraightAuton();
        void init() override;
        AutonStatus loop() override;

    protected:
        void on_exit() override;
};
