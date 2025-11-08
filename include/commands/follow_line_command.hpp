#include "command.hpp"

class FollowLineCommand : public Command<FollowLineCommand> {
    public:
        void init() override;
        CommandStatus loop() override;

    protected:
        void on_exit() override;
};
