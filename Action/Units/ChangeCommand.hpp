#ifndef CHANGE_COMMAND
#define CHANGE_COMMAND

#include "Command.hpp"

class ChangeCommand : public Command
{
    public:
        ChangeCommand(std::vector<std::string> &tokens);

        void execute(LibrService &service) const override;

    private:
        std::vector<std::string> tokens;
};

#endif