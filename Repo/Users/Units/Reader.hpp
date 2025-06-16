#ifndef READER_HEADER
#define READER_HEADER

#include "User.hpp"

class Reader : public User
{
    public:

        Reader(std::ifstream& file);
        Reader(const std::string &username, const std::string &password);

        void borrowPaper(int paperID, time_t due);
        void returnPaper(int paperID);

        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;

        User *clone() const override;
        User::UserType getUserType() const override { return User::READER; }
        std::vector<BorrowedPaper> &getBooksTaken() override { return borrowedPapers; };
        void takeBook(unsigned id) override;
        void giveBook(unsigned id) override;

    private:
        void printBorrowedPaper(unsigned idx) const;
        void readBorrowedPaper(std::ifstream &in, BorrowedPaper& borr);
        void writeBorrowedPaper(std::ofstream &out, const BorrowedPaper& borr) const;

    private:
        std::vector<BorrowedPaper> borrowedPapers;

};

#endif
