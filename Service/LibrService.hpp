#ifndef LIBR_SERVICE_HEADER
#define LIBR_SERVICE_HEADER

#include "../Repo/Libr/LibrRepo.hpp"
#include "../Repo/Users/UserRepo.hpp"

/// @brief Service layer class that handles operations on books and users.
class LibrService
{
    public:
        /// @brief Default constructor.
        LibrService() = default;

        /// @brief Constructs the service with input file streams for books, taken books, and users.
        /// @param libr Input stream for library books.
        /// @param taken Input stream for taken books.
        /// @param users Input stream for users.
        LibrService(std::ifstream &libr, std::ifstream& taken, std::ifstream &users);

        /// @brief Attempts to log in a user.
        /// @param username The username.
        /// @param password The password.
        void login(const std::string &username, const std::string &password);

        /// @brief Logs out the currently logged in user.
        void logout();

        /// @brief Shows all books in the library.
        void showBooks() const;

        /// @brief Shows all periodicals.
        void showPerodical() const;

        /// @brief Shows all series.
        void showSeries() const;

        /// @brief Shows all types of papers.
        void showAll() const;

        /// @brief Shows detailed information about a book by ISBN.
        /// @param isbn The ISBN string.
        void getInfo(const std::string &isbn) const;

        /// @brief Adds a new book to the library.
        /// @param book Pointer to the book to add.
        void addBook(Papers* book);

        /// @brief Removes a book by its ID.
        /// @param id The book ID.
        void removeBook(unsigned id);

        /// @brief Modifies a book by its ID.
        /// @param id The book ID.
        void changeBook(unsigned id);

        /// @brief Finds papers by specified options.
        /// @param option Field to search by.
        /// @param value Value to match.
        /// @param type Type of paper.
        /// @param sorted Whether results should be sorted.
        /// @param asc Sort order ascending if true.
        /// @param key Optional keyword.
        /// @param top Limit of results.
        void findPaper(const std::string &option, const std::string &value, Papers::Type type,
                       bool sorted = false, bool asc = true, const std::string &key = "", int top = 0);

        /// @brief Adds a new user.
        /// @param user Pointer to user to add.
        void addUser(User *user);

        /// @brief Removes a user by pointer.
        /// @param user Pointer to user to remove.
        void removeUser(User *user);

        /// @brief Removes a user by username.
        /// @param username Username of the user to remove.
        void removeUser(const std::string &username);

        /// @brief Changes the password of the currently logged-in user.
        /// @param pass New password.
        void changeSelfPass(const std::string &pass);

        /// @brief Changes the password of another user.
        /// @param username Username of the user.
        /// @param pass New password.
        void changeOtherPass(const std::string &username, const std::string &pass);

        /// @brief Finds users by name.
        /// @param name The name to search.
        void findUserName(const std::string &name) const;

        /// @brief Finds users borrowed book with ID.
        /// @param id The book ID.
        void findUserId(unsigned id) const;

        /// @brief Finds users by status.
        /// @param status The user status.
        void findUserStatus(const std::string &status) const;

        /// @brief Takes a book by ID (borrow).
        /// @param id Book ID.
        void take(unsigned id);

        /// @brief Returns a book by ID.
        /// @param id Book ID.
        void give(unsigned id);

        /// @brief Saves all data to files.
        /// @param libr Output stream for books.
        /// @param taken Output stream for taken books.
        /// @param users Output stream for users.
        void save(std::ofstream &libr, std::ofstream& taken, std::ofstream &users);

        /// @brief Checks if the current user is admin, throws if not.
        void adminOnly() const;

        /// @brief Checks if the current user is reader, throws if not.
        void readerOnly() const;

        /// @brief Checks if a user is logged in, throws if not.
        void checkLogged() const;
        
    private:
        LibrRepo books;                 ///< Repository of all books.
        LibrRepo taken;                 ///< Repository of taken books.
        UserRepo users;                 ///< Repository of all users.

        User *loggedUser = nullptr;     ///< Currently logged in user pointer.  
};

#endif