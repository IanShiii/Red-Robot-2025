#pragma once

#include <Arduino.h>
#include "commands/command.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/line_sensor.hpp"

#define MAX_AUTON_DURATION_MILLISECONDS 20000 // 20 seconds

class MoveStraightAuton : public Command<MoveStraightAuton> {
    double DURATION_MILLISECONDS = 10000; // 10 seconds

    public:
        MoveStraightAuton();
        void init() override;
        CommandStatus loop() override;

    protected:
        void on_exit() override;
};
