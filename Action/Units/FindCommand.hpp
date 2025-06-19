#ifndef FIND_COMMAND
#define FIND_COMMAND

#include "Command.hpp"

class FindCommand : public Command
{
    public:
        FindCommand(std::vector<std::string> &tokens);

        void execute(LibrService &service) const override;
    
    private:
        void findUser(LibrService& service) const;
        void findBook(LibrService& service) const;

    private:
        std::vector<std::string> tokens;
};

#endif

