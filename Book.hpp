#ifndef BOOK_HEADER
#define BOOK_HEADER

#include "Papers.hpp"



class Book : virtual public Papers
{
    public:
        // Constructors
        Book(std::ifstream& file);
        Book(const std::string &title, const std::string &publisher, const std::string &description,
             const std::string &isbn, unsigned yearPublished, double rating, 
             const std::string &genre, const std::vector<std::string>& keyWords);

        Book(const Book &other);
        Book &operator=(const Book &other);
        ~Book() {};

        // Selectors
        const std::vector<std::string> &getKeyWords() const { return keyWords; }

        // Mutators
        void setKeyWords(const std::vector<std::string> &keyWords);

        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;

        Type getType() const override { return Papers::BOOK; }
        Papers *clone() const override;
    
    protected:
        void print() const;
        void save(std::ofstream &out) const;

    private:
        std::vector<std::string> keyWords;
};
#endif