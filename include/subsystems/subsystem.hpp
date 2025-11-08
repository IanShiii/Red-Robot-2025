#pragma once

class Subsystem {
    public:
        virtual void loop() = 0;
        virtual void log() = 0;
    protected:
        Subsystem() = default;
};
