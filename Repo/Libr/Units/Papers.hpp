#ifndef PAPERS_HEADER
#define PAPERS_HEADER

#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>


class Papers
{
    public:
        enum Genre
        {
            UNKNOWN,
            DRAMA,
            HORROR,
            MYSTERY,
            GENRE_COUNT
        };

        enum Type
        {
            BOOK,
            PERIODICAL,
            SERIES,
            ALL
        };

        // Constructors
        Papers(std::ifstream& file);
        Papers(const std::string &title, const std::string &publisher, const std::string &description, 
               const std::string &isbn, unsigned yearPublished, double rating, const std::string &genre);

        Papers(const Papers &other);
        Papers &operator=(const Papers &other);
        virtual ~Papers() = default;

        // Selectors
        const std::string &getTitle() const       { return title; };
        const std::string &getPublisher() const   { return publisher; };
        const std::string &getDescription() const { return description; };
        const std::string &getISBN() const        { return isbn; };
        unsigned getYearPublished() const         { return yearPublished; };
        unsigned getID() const                    { return id; };
        double getRating() const                  { return rating; };
        Genre getGenre() const                    { return genre; };

        bool matchTitle(const std::string &title) const;
        virtual bool matchAutor(const std::string &autor) const { return false; }
        virtual bool matchTaggs(const std::string &taggs) const { return false; }

        // Mutators
        void setTitle(const std::string &title);
        void setPublisher(const std::string &publisher);
        void setDescription(const std::string &description);
        void setISBN(const std::string &isbn);
        void setYear(unsigned year);
        void setRating(double rating);
        void setGenre(const std::string &genre);

        void printShort() const;

        virtual void printInfo() const;
        virtual void saveOnFile(std::ofstream &out) const;
        virtual void change();
        
        virtual Type getType() const = 0;
        virtual Papers *clone() const = 0;

        static bool compare(const Papers *first, const Papers *second, const std::string &value);

    private:
        void copy(const Papers &other);
        unsigned readId(std::ifstream &in) const;
        
    protected:
        static Genre stringToGenre(const std::string &text);
        static const char *genreToString(Genre genre);
        static void readString(std::ifstream &file, std::string& str);
        static void writeString(std::ofstream &out, const std::string &str);

    private:
        std::string title;
        std::string publisher;
        std::string description;
        std::string isbn;
        unsigned yearPublished;
        const unsigned id;
        double rating;
        Genre genre;

        static unsigned nextId;
};

#endif