#ifndef ADMIN_HEADER
#define ADMIN_HEADER

#include "User.hpp"

/// @brief Represents an administrator user with special privileges.
class Admin : public User
{
    public:
        /// @brief Constructs an Admin object by reading from a file.
        /// @param file Input file stream.
        Admin(std::ifstream &file);

        /// @brief Constructs an Admin object with given credentials.
        /// @param username The admin's username.
        /// @param password The admin's password.
        /// @param email The admin's email.
        Admin(const std::string &username, const std::string &password, const std::string &email);

        /// @brief Returns the admin's email.
        /// @return Email as const reference.
        const std::string &getEmail() const { return this->email; }

        /// @brief Prints admin information.
        void printInfo() const override;

        /// @brief Saves admin data to file.
        /// @param out Output file stream.
        void saveOnFile(std::ofstream &out) const override;

        /// @brief Clones the Admin object.
        /// @return Pointer to the new Admin copy.
        User *clone() const override;

        /// @brief Returns the user type (ADMIN).
        /// @return UserType enum value.
        User::UserType getUserType() const override { return User::ADMIN; }

        /// @brief Throws an exception
        std::vector<BorrowedPaper> &getBooksTaken() override;

        /// @brief Stub for takeBook (Admin does not use).
        /// @param id 
        void takeBook(unsigned id) override {};

        /// @brief Stub for giveBook (Admin does not use).
        /// @param id 
        void giveBook(unsigned id) override {};

    private:
        /// @brief Validates the email format.
        /// @param email The email string to validate.
        /// @return true if valid, false otherwise.
        static bool validEmail(const std::string &email);

    private:
        std::string email;      ///< The email address of the admin.
};

#endif