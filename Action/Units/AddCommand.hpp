#ifndef ADD_COMMAND
#define ADD_COMMAND

#include "Command.hpp"

/// @brief Command that adds paper or user to the database
class AddCommand : public Command
{
    public:
        /// @brief Ctor of the class
        /// @param tokens A vector of string tokens representing the command and its arguments.
        AddCommand(std::vector<std::string>& tokens);

        /// @brief Executes the command using the provided library service.
        /// @param service A reference to the library service on which to execute the command.
        void execute(LibrService &service) const override;
    
    private:
        /// @brief Adds a new user to the library system.
        /// @param service service Reference to the LibrService that manages user data.
        void addUser(LibrService& service) const;

        /// @brief Adds a new paper to the library system.
        /// @param service Reference to the LibrService responsible for managing papers.
        void addPaper(LibrService& service) const;

        /// @brief Reads and processes metadata for a paper.
        /// @param title Reference to a string that will hold the paper's title.
        /// @param publisher Reference to a string that will hold the publisher's name.
        /// @param description Reference to a string for the paper's description or abstract.
        /// @param isbn Reference to a string for the paper's ISBN or unique identifier.
        /// @param yearPublished The year the paper was published.
        /// @param rating The rating of the paper (e.g., from user input or database).
        /// @param genre Reference to a string for the paper's genre or category.
        void readPaper(std::string &title, std::string &publisher, std::string &description,
                       std::string &isbn, unsigned yearPublished, double rating, std::string &genre) const;

        /// @brief Reads and processes metadata for a book.
        /// @param keyWords Reference to a vector of strings to store the book's keywords.
        /// @param autor Reference to a string to store the author's name.
        void readBook(std::vector<std::string> &keyWords, std::string& autor) const;

        /// @brief Reads and processes metadata for a periodical.
        /// @param month Reference to an unsigned int that will hold the publication month.
        /// @param issue Reference to an unsigned int that will hold the issue number.
        /// @param articles Reference to a vector of Periodical::Article objects representing the articles in the periodical.
        void readPeri(unsigned &month, unsigned &issue, std::vector<Periodical::Article> &articles) const;

    private:
        /// @brief Stores the list of command tokens parsed from input.
        std::vector<std::string> tokens;
};

#endif