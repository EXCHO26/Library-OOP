#ifndef USER_HEADER
#define USER_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class User
{
    public:

        enum UserType
        {
            UNKNOWN,
            READER,
            ADMIN,
            USERTYPE_COUNT
        };

        User(std::ifstream& file);
        User(const std::string &username, const std::string &password);
        virtual ~User() {};

        const std::string &getUsername() const { return username; }
        const std::string &getPassword() const { return password; }
        time_t getRegisteredAt() const         { return registeredAt; }
        time_t getLastLoginAt() const          { return lastLoginAt; }

        void setUsername(const std::string &username);
        void setPassword(const std::string &password);
        bool login(const std::string& pass);

        virtual void printInfo() const;
        virtual void saveOnFile(std::ofstream &out) const;

        virtual User* clone() const = 0;
        virtual UserType getUserType() const = 0;

    protected:
        static void readString(std::ifstream &file, std::string &str);
        static void writeString(std::ofstream &out, const std::string &str);
        static time_t getTimeFromFile(std::ifstream &in);

    private:
        std::string username;
        std::string password;
        const time_t registeredAt;
        time_t lastLoginAt;
};

#endif