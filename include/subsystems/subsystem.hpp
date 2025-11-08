#pragma once

template <typename T>
class Subsystem {
    public:
        static T& get_instance() {
            static T instance;
            return instance;
        }

        virtual void loop() = 0;
        virtual void log() = 0;
    protected:
        Subsystem() = default;
};
