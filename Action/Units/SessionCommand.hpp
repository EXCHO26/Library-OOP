#ifndef SESSION_COMMAND
#define SESSION_COMMAND

#include "Command.hpp"

/// @brief Handles user session actions such as login, logout, and exit.
class SessionCommand : public Command
{
    public:
        /// @brief Defines possible session actions.
        enum Action
        {
            LOGIN,
            LOGOUT,
            EXIT
        };

        /// @brief Constructs a SessionCommand with the specified action and optional credentials.
        /// @param act The session action to perform (LOGIN, LOGOUT, EXIT).
        /// @param username The username for login action (optional).
        /// @param pass The password for login action (optional).
        SessionCommand(Action act, const std::string& username = "", const std::string& pass = "");

        /// @brief Executes the session command on the given library service.
        /// @param service Reference to the LibrService handling session management.
        void execute(LibrService &service) const override;

    private:
        /// @brief The action to perform in the session
        Action act;

        /// @brief Username for login
        std::string username;

        /// @brief Password for login
        std::string password;
};

#endif