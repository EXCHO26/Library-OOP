#include "Admin.hpp"

bool Admin::validEmail(const std::string &email)
{
    if (email.front() == '@' || email.back() == '@') return false;

    bool hasOneAt = false;
    for (int i = 0; i < email.size(); i++)
    {
        if (email[i] == '@')
        {
            if (!hasOneAt) hasOneAt = true;
            else return false;
        }
    }
    return hasOneAt;
}

Admin::Admin(std::ifstream &file) : User(file)
{
    if (!file) throw std::invalid_argument("Cannot open the file to create admin!");

    User::readString(file, this->email);

    if (!file) throw std::invalid_argument("Failed to create admin!");
}

Admin::Admin(const std::string &username, const std::string &password, const std::string &email)
    : User(username, password), email(email) 
{};


void Admin::printInfo() const
{
    this->User::printInfo();
    std::cout << this->email << '\n';
}

void Admin::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open file to save the admin!");

    UserType type = getUserType();
    out.write((const char *)&type, sizeof(type));

    this->User::saveOnFile(out);

    User::writeString(out, this->email);

    if (!out) throw std::invalid_argument("Failed to save the admin!");
}

User* Admin::clone() const
{
    return new Admin(*this);
}

std::vector<User::BorrowedPaper>& Admin::getBooksTaken()
{
    throw std::logic_error("Admins dont have books taken!");
}