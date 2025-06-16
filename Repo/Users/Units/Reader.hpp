#ifndef READER_HEADER
#define READER_HEADER

#include <vector>

#include "User.hpp"

class Reader : public User
{
    public:

        struct BorrowedPaper
        {
            int paperID;
            time_t borrowedAt;
            time_t dueAt;
            bool isReturned;
        };

        Reader(std::ifstream& file);
        Reader(const std::string &username, const std::string &password);

        void borrowPaper(int paperID, time_t due);
        void returnPaper(int paperID);

        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;

        User *clone() const override;
        User::UserType getUserType() const override { return User::READER; }

    private:
        void printBorrowedPaper(unsigned idx) const;
        void readBorrowedPaper(std::ifstream &in, BorrowedPaper& borr);
        void writeBorrowedPaper(std::ofstream &out, const BorrowedPaper& borr) const;

    private:
        std::vector<BorrowedPaper> borrowedPapers;

};

#endif
