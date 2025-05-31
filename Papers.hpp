#ifndef PAPERS_HEADER
#define PAPERS_HEADER

#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>

class Papers
{
    public:
        enum Genre
        {
            UNKNOWN,
            DRAMA,
            HORROR,
            MISTERY,
            GENRE_COUNT
        };

        Papers(std::ifstream& file);
        Papers(std::string &title, std::string &pub, std::string &desc, std::string isbn, int year, double rating, std::string &genre);
        Papers(const Papers &other);
        Papers &operator=(const Papers &other);
        virtual ~Papers();

        std::string *getTitle() const;
        std::string *getPublisher() const;
        std::string *getDescription() const;
        std::string *getISBN() const;
        int *getYearPublished() const;
        int *getID() const;
        Genre *getGenre() const;

        void setTitle(std::string &title);
        void setPublisher(std::string &publisher);
        void setISBN(std::string &isbn);
        void setYear(int year);
        void setRating(double rating);
        void setGenre(std::string &genre);

        virtual Papers *clone() const = 0;
        virtual void printInfo() const = 0;

    private:
        Genre stringToGenre(std::string &text) const;

    private:
        std::string title;
        std::string publisher;
        std::string description;
        std::string isbn;
        int yearPublished;
        const int id;
        double rating;
        Genre genre;

        static int nextId;
};

#endif