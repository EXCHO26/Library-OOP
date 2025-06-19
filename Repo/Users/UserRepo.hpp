#ifndef USER_REPO_HEADER
#define USER_REPO_HEADER

#include <cmath>

#include "Units/Reader.hpp"
#include "Units/Admin.hpp"


/// @brief Repository class for managing all User objects (Admins and Readers).
class UserRepo
{
    public:
        /// @brief Default constructor.
        UserRepo();

        /// @brief Constructs the repository by loading from file.
        /// @param in Input file stream.
        UserRepo(std::ifstream& in);

        /// @brief Copy constructor.
        UserRepo(const UserRepo &other);

        /// @brief Assignment operator.
        UserRepo &operator=(const UserRepo &other);

        /// @brief Destructor.
        ~UserRepo();

        /// @brief Adds a new user to the repository.
        /// @param paper Pointer to a dynamically allocated User object.
        void addUser(User *paper);

        /// @brief Removes a user by username.
        /// @param username The username to remove.
        void removeUser(const std::string& username);

        /// @brief Returns the current number of users.
        unsigned getSize() const { return size; }

        /// @brief Displays all users with a matching name.
        /// @param name The name to match.
        void showAllWithName(const std::string &name) const;

        /// @brief Displays all users who have borrowed a book with the given ID.
        /// @param id The paper ID.
        void showAllWithBook(unsigned id) const;

        /// @brief Displays all users with overdue books.
        void showAllOverdue() const;

        /// @brief Displays all users of type Reader.
        void showAllReaders() const;

        /// @brief Displays all users who haven't borrowed anything.
        void showAllInactive() const;

        /// @brief Prints a specific user by index.
        /// @param idx Index of the user.
        void printUser(unsigned idx) const;

        /// @brief Saves all user data to an output file stream.
        /// @param out Output stream.
        void save(std::ofstream& out) const;

        /// @brief Retrieves a user by username.
        /// @param username Username of the user.
        /// @return Pointer to the user object if found, nullptr otherwise.
        User* operator[](const std::string &username);

        /// @brief Retrieves a user by index.
        /// @param idx Index of the user.
        /// @return Pointer to the user object.
        User* operator[](unsigned idx);

        /// @brief Counts the number of Admin users in the repository.
        int adminCount() const;

    private:
        /// @brief Helper to make a deep copy of another repository.
        /// @param other The repository to copy.
        /// @param newCapacity Capacity of the new repository.
        User **copyRepo(const UserRepo &other, unsigned newCapacity);

        /// @brief Doubles the internal array capacity.
        void resize();

        /// @brief Frees all dynamically allocated memory.
        void free();

        /// @brief Ensures the username is unique in the repository.
        /// @param name Username to check.
        /// @return True if unique, false otherwise.
        bool uniqueUser(const std::string &name);

        /// @brief Factory method to create a user from file.
        /// @param in Input file stream.
        /// @return Pointer to a new User object.
        User* factory(std::ifstream &in) const;

    private:
        User **repo;            ///< Array of pointers to User objects.
        unsigned size;          ///< Current number of users.
        unsigned capacity;      ///< Allocated capacity.
};

#endif