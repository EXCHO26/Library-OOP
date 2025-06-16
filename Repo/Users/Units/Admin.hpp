#ifndef ADMIN_HEADER
#define ADMIN_HEADER

#include "User.hpp"

class Admin : public User
{
    public:
        Admin(std::ifstream &file);
        Admin(const std::string &username, const std::string &password, const std::string &email);

        const std::string &getEmail() const { return this->email; }

        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;

        User *clone() const override;
        User::UserType getUserType() const override { return User::ADMIN; }
        std::vector<BorrowedPaper> &getBooksTaken() override;
        void takeBook(unsigned id) override {};
        void giveBook(unsigned id) override {};

    private:
        static bool validEmail(const std::string &email);

    private:
        std::string email;
};

#endif