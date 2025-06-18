#ifndef SESSION_COMMAND
#define SESSION_COMMAND

#include "Command.hpp"

class SessionCommand : public Command
{
    public:
        enum Action
        {
            LOGIN,
            LOGOUT,
            EXIT
        };

        SessionCommand(Action act, const std::string& username = "", const std::string& pass = "");

        void execute(LibrService &service) override;

    private:
        Action act;
        std::string username, password;
};

#endif