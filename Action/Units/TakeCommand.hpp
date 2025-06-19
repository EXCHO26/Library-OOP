#ifndef TAKE_COMMAND
#define TAKE_COMMAND

#include "Command.hpp"

class TakeCommand : public Command
{
    public:
        TakeCommand(std::vector<std::string> &tokens);

        void execute(LibrService &service) const override;

    private:
        std::vector<std::string> tokens;
};

#endif