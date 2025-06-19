#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include "../../Service/LibrService.hpp"

/// @brief Abstract base class for all commands acting on LibrService.
class Command
{
    public:
        /// @brief Virtual destructor.
        virtual ~Command() = default;

        /// @brief Executes the command on the given library service.
        /// @param service Reference to the LibrService on which the command operates.
        virtual void execute(LibrService& service) const = 0;

    protected:
        /// @brief Converts a string to an unsigned index.
        /// @param line The input string to convert.
        /// @return The unsigned integer index parsed from the string.
        static unsigned stringToIndex(const std::string &line);
};

#endif
