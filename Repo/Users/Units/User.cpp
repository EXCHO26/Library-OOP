#include "User.hpp"

void User::readString(std::ifstream &file, std::string &str)
{
    if (!file) throw std::invalid_argument("Cannot open the file for reading string.");

    unsigned length;
    file.read((char*)&length, sizeof(length));
    if (!file) throw std::runtime_error("Failed to read string length.");

    str.resize(length);

    file.read(&str[0], length);
    if (!file) throw std::runtime_error("Failed to read string.");
}

void User::writeString(std::ofstream &out, const std::string &str)
{
    if (!out) throw std::invalid_argument("Cannot open the file for writing string.");

    unsigned length = str.size();
    out.write((const char*)&length, sizeof(length));
    out.write(str.c_str(), length);

    if (!out) throw std::runtime_error("Failed to write string.");
}

time_t User::getTimeFromFile(std::ifstream &in)
{
    if (!in) throw std::invalid_argument("Cannot open the file to read the time!");

    time_t time;
    in.read((char *)&time, sizeof(time));

    if (!in) throw std::invalid_argument("Failed to read the time!");

    return time;
}

User::User(std::ifstream& file) 
    : registeredAt(getTimeFromFile(file)),
      lastLoginAt(getTimeFromFile(file))
{
    if (!file) throw std::invalid_argument("Cannot open the file for reading user data.");

    readString(file, username);
    readString(file, password);

    if (username.empty() || password.empty()) throw std::runtime_error("Username or password cannot be empty.");

    
}

User::User(const std::string &username, const std::string &password)
    : username(username), password(password), registeredAt(std::time(nullptr)), lastLoginAt(std::time(nullptr))
{
    if (username.empty() || password.empty()) throw std::runtime_error("Username or password cannot be empty.");
}

void User::setUsername(const std::string &username)
{
    if (username.empty()) throw std::invalid_argument("Username cannot be empty.");
    this->username = username;
}

void User::setPassword(const std::string &password)
{
    if (password.empty()) throw std::invalid_argument("Password cannot be empty.");
    this->password = password;
}

bool User::login(const std::string& pass)
{
    if (password == pass)
    {
        this->lastLoginAt = std::time(nullptr);
        return true;
    }
    return false;
}

void User::printInfo() const
{
    std::cout << "Username: " << username << "\n";
    std::cout << "Registered At: " << std::ctime(&registeredAt);
    std::cout << "Last Login At: " << std::ctime(&lastLoginAt);
}

void User::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for writing user data.");

    out.write((const char*)&registeredAt, sizeof(registeredAt));
    out.write((const char*)&lastLoginAt, sizeof(lastLoginAt));

    writeString(out, username);
    writeString(out, password);

    if (!out) throw std::runtime_error("Failed to write user data to file.");
}

