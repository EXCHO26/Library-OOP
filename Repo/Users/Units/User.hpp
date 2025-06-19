#ifndef USER_HEADER
#define USER_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

/// @brief Abstract base class representing a generic user of the library system.
class User
{
    public:
        /// @brief Enumerates the possible types of users.
        enum UserType
        {
            UNKNOWN,
            READER,
            ADMIN,
            USERTYPE_COUNT
        };

        /// @brief Represents a borrowed paper entry by a user.
        struct BorrowedPaper
        {
            unsigned paperID;       ///< ID of the paper.
            time_t borrowedAt;      ///< Timestamp of when the paper was borrowed.
            time_t dueAt;           ///< Timestamp of when the paper is due.
            bool isReturned;        ///< Indicates if the paper has been returned.
        };

        /// @brief Constructs a User object from file.
        /// @param file Input file stream.
        User(std::ifstream& file);

        /// @brief Constructs a User with a username and password.
        /// @param username The username.
        /// @param password The password.
        User(const std::string &username, const std::string &password);

        /// @brief Virtual destructor.
        virtual ~User() {};

        /** @name Accessors */
        ///@{
        const std::string &getUsername() const { return username; }
        const std::string &getPassword() const { return password; }
        time_t getRegisteredAt() const         { return registeredAt; }
        time_t getLastLoginAt() const          { return lastLoginAt; }
        ///@}

        /// @brief Sets the username.
        /// @param username New username.
        void setUsername(const std::string &username);

        /// @brief Sets the password.
        /// @param password New password.
        void setPassword(const std::string &password);

        /// @brief Attempts to log in with the given password.
        /// @param pass he input password to validate.
        /// @return True if password matches and login is successful.
        bool login(const std::string& pass);

        /// @brief Prints user information.
        virtual void printInfo() const;

        /// @brief Saves user information to a file.
        /// @param out Output file stream.
        virtual void saveOnFile(std::ofstream &out) const;

        /// @brief Clones the user object.
        /// @return Pointer to a deep copy of the user.
        virtual User* clone() const = 0;

        /// @brief Returns the type of user.
        /// @return UserType enum.
        virtual UserType getUserType() const = 0;

        /// @brief Returns a reference to the list of borrowed papers.
        virtual std::vector<BorrowedPaper>& getBooksTaken() = 0;

        /// @brief Marks a paper as borrowed.
        /// @param id Paper ID.
        virtual void takeBook(unsigned id) = 0;

        /// @brief Marks a paper as returned.
        /// @param id Paper ID.
        virtual void giveBook(unsigned id) = 0;

    protected:
        /// @brief Helper to read a string from a file.
        static void readString(std::ifstream &file, std::string &str);

        /// @brief Helper to write a string to a file.
        static void writeString(std::ofstream &out, const std::string &str);

        /// @brief Helper to read a time_t value from file.
        static time_t getTimeFromFile(std::ifstream &in);

    private:
        std::string username;           ///< The user's login name.
        std::string password;           ///< The user's password.
        const time_t registeredAt;      ///< Timestamp of account creation.
        time_t lastLoginAt;             ///< Timestamp of last successful login.
};

#endif