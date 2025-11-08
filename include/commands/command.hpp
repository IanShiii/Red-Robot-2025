#pragma once

enum CommandStatus {IN_PROGRESS, DONE};

template <typename T>
class Command {
    public:
        virtual void init() = 0;
        virtual CommandStatus loop() = 0;

    protected:
        unsigned long start_time_milliseconds_;
        
        virtual void on_exit() = 0;
};
