#ifndef RETURN_COMMAND
#define RETURN_COMMAND

#include "Command.hpp"

/// @brief Command to handle the return of items in the library system.
class ReturnCommand : public Command
{
    public:
        /// @brief Constructs a ReturnCommand with the provided tokens.
        /// @param tokens A vector of strings representing the return command tokens.
        ReturnCommand(std::vector<std::string> &tokens);

        /// @brief Executes the return command on the provided library service.
        /// @param service Reference to the LibrService handling the return process.
        void execute(LibrService &service) const;

    private:
        /// @brief Stores the tokens that define the return command.
        std::vector<std::string> tokens;
};

#endif