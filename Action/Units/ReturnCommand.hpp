#ifndef RETURN_COMMAND
#define RETURN_COMMAND

#include "Command.hpp"

class ReturnCommand : public Command
{
    public:
        ReturnCommand(std::vector<std::string> &tokens);

        void execute(LibrService &service) const;

    private:
        std::vector<std::string> tokens;
};

#endif