#ifndef INFO_COMMAND
#define INFO_COMMAND

#include "Command.hpp"

/// @brief Command to display or retrieve information from the library system.
class InfoCommand : public Command
{
    public:
        /// @brief Constructs an InfoCommand with a reference to tokens.
        /// @param tokens Reference to a vector of strings representing the command tokens.
        InfoCommand(std::vector<std::string> &tokens);

        /// @brief Executes the info command on the provided library service.
        /// @param service The LibrService instance used to retrieve information.
        void execute(LibrService &service) const override;

    private:
        /// @brief Reference to the tokens representing the command arguments.
        std::vector<std::string> &tokens;
};

#endif