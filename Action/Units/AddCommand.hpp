#ifndef ADD_COMMAND
#define ADD_COMMAND

#include "Command.hpp"

class AddCommand : public Command
{
    public:
        AddCommand(std::vector<std::string>& tokens);

        void execute(LibrService &service) const override;
    
    private:
        void addUser(LibrService& service) const;

        void addPaper(LibrService& service) const;
        void readPaper(std::string &title, std::string &publisher, std::string &description,
                       std::string &isbn, unsigned yearPublished, double rating, std::string &genre) const;

        void readBook(std::vector<std::string> &keyWords, std::string& autor) const;
        void readPeri(unsigned &month, unsigned &issue, std::vector<Periodical::Article> &articles) const;

    private:
        std::vector<std::string> tokens;
};

#endif