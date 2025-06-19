#ifndef READER_HEADER
#define READER_HEADER

#include "User.hpp"

/// @brief Represents a library reader who can borrow and return papers.
class Reader : public User
{
    public:
        /// @brief Constructs a Reader object from a file stream.
        /// @param file Input file stream.
        Reader(std::ifstream& file);

        /// @brief Constructs a Reader object with a username and password.
        /// @param username The reader's username.
        /// @param password The reader's password.
        Reader(const std::string &username, const std::string &password);

        /// @brief Borrows a paper by ID with a specified due date.
        /// @param paperID ID of the paper to borrow.
        /// @param due Time (timestamp) when the paper is due.
        void borrowPaper(int paperID, time_t due);

        /// @brief Returns a borrowed paper by ID.
        /// @param paperID ID of the paper to return.
        void returnPaper(int paperID);

        /// @brief Prints information about the reader.
        void printInfo() const override;

        /// @brief Saves reader data to a file.
        /// @param out Output file stream.
        void saveOnFile(std::ofstream &out) const override;

        /// @brief Creates a deep copy of the Reader object.
        /// @return Pointer to the copied Reader.
        User *clone() const override;

        /// @brief Returns the type of user.
        /// @return UserType enum value (READER).
        User::UserType getUserType() const override { return User::READER; }

        /// @brief Returns a reference to the borrowed papers list.
        /// @return Reference to vector of BorrowedPaper.
        std::vector<BorrowedPaper> &getBooksTaken() override { return borrowedPapers; };

        /// @brief Registers a book as borrowed by ID.
        /// @param id Paper ID.
        void takeBook(unsigned id) override;

        /// @brief Removes a borrowed book by ID.
        /// @param id Paper ID.
        void giveBook(unsigned id) override;

    private:
        /// @brief Reads a BorrowedPaper record from file.
        /// @param in Input file stream.
        /// @param borr Reference to BorrowedPaper object to fill.
        void readBorrowedPaper(std::ifstream &in, BorrowedPaper& borr);

        /// @brief Writes a BorrowedPaper record to file.
        /// @param out Output file stream.
        /// @param borr The BorrowedPaper to write.
        void writeBorrowedPaper(std::ofstream &out, const BorrowedPaper& borr) const;

    private:
        std::vector<BorrowedPaper> borrowedPapers;      ///< List of papers borrowed by the reader.

};

#endif
