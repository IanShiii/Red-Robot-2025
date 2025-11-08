#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <servo.pio.h>
#include "pins.hpp"
#include "subsystem.hpp"
#include "settings.hpp"

class Gate : public Subsystem {
    public:
        static Gate& get_instance() {
            static Gate instance;
            return instance;
        }

        void loop() override;
        void log() override;

        void open();
        void close();
        void set_angle_degrees(int angle);

    private:
        friend class Subsystem;
        Gate();

        Servo servo_;

};
