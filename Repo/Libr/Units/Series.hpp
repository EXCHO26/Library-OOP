#ifndef SERIES_HPP
#define SERIES_HPP

#include "Book.hpp"
#include "Periodical.hpp"


class Series : public Book, public Periodical
{
    public:
        // Constructors
        Series(std::ifstream& file);
        Series(const std::string &title, const std::string &publisher, const std::string &description,
               const std::string &isbn, unsigned yearPublished, double rating, 
               const std::string &genre, unsigned month, unsigned issueNumber,
               const std::vector<Periodical::Article> &articles,
               const std::vector<std::string>& keyWords,
               const std::string &autor);

        Series(const Series &other);
        Series &operator=(const Series &other);
        ~Series() {};

        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;
        bool matchAutor(const std::string &autor) const override;
        bool matchTaggs(const std::string &taggs) const override;

        void change() override;
        Type getType() const override { return Papers::SERIES; }
        Papers *clone() const override;
    private:
};

#endif