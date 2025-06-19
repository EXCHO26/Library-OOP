#ifndef FIND_COMMAND
#define FIND_COMMAND

#include "Command.hpp"

/// @brief Implements a command to find users or books in the library system.
class FindCommand : public Command
{
    public:
        /// @brief Constructs a FindCommand with the given tokens.
        /// @param tokens A vector of strings representing the command tokens.
        FindCommand(std::vector<std::string> &tokens);

        /// @brief Executes the find command on the given library service.
        /// @param service The LibrService instance used to perform the search.
        void execute(LibrService &service) const override;
    
    private:
        /// @brief Searches for a user in the library service.
        /// @param service Reference to the LibrService for user lookup.
        void findUser(LibrService& service) const;

        /// @brief Searches for a book in the library service.
        /// @param service Reference to the LibrService for book lookup.
        void findBook(LibrService& service) const;

    private:
        /// @brief Stores the command tokens used to determine the find criteria.
        std::vector<std::string> tokens;
};

#endif

