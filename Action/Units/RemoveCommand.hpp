#ifndef REMOVE_COMMAND
#define REMOVE_COMMAND

#include "Command.hpp"

/// @brief Command to remove an entity from the library system.
class RemoveCommand : public Command
{
    public:
        /// @brief Constructs a RemoveCommand with the given tokens.
        /// @param tokens A vector of strings representing the command tokens.
        RemoveCommand(std::vector<std::string> &tokens);

        /// @brief Executes the remove command on the given library service.
        /// @param service The LibrService instance on which the removal is performed.
        void execute(LibrService& service) const override;

    private:
        /// @brief Stores the tokens representing the remove command details.
        std::vector<std::string> tokens;
};

#endif