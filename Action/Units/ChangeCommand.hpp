#ifndef CHANGE_COMMAND
#define CHANGE_COMMAND

#include "Command.hpp"

/**
 * @class ChangeCommand
 * @brief Represents a command to change or update library data.
 * 
 */
class ChangeCommand : public Command
{
    public:
        /// @brief Constructs a ChangeCommand with the given tokens.
        /// @param tokens A vector of strings representing the command tokens.
        ChangeCommand(std::vector<std::string> &tokens);

        /// @brief Executes the change command on the given library service.
        /// @param service The LibrService instance on which the command operates.
        void execute(LibrService &service) const override;

    private:
        /// @brief Stores the tokens representing the command.
        std::vector<std::string> tokens;
};

#endif