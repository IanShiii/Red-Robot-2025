#pragma once

#include <Arduino.h>

#define AUTON_DURATION_MILLISECONDS 20000 // 20 seconds

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

class Auton1 : public Auton<Auton1> {
    public:
        Auton1();
        void init() override;
        AutonStatus loop() override;

    protected:
        void on_exit() override;
};
