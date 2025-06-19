#ifndef TAKE_COMMAND
#define TAKE_COMMAND

#include "Command.hpp"

/// @brief Command to handle taking or borrowing items from the library system.
class TakeCommand : public Command
{
    public:
        /// @brief Constructs a TakeCommand with the given tokens.
        /// @param tokens A vector of strings representing the take command details.
        TakeCommand(std::vector<std::string> &tokens);

        /// @brief Executes the take command on the provided library service.
        /// @param service Reference to the LibrService managing borrowing operations.
        void execute(LibrService &service) const override;

    private:
        /// @brief Stores the tokens representing the command arguments.
        std::vector<std::string> tokens;
};

#endif