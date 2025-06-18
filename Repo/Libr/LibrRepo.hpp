#ifndef LIBR_REPO_HEADER
#define LIBR_REPO_HEADER

#include <cmath>

#include "Units/Series.hpp"


class LibrRepo
{
    public:
        LibrRepo();
        LibrRepo(std::ifstream& in);
        LibrRepo(const LibrRepo &other);
        LibrRepo &operator=(const LibrRepo &other);
        ~LibrRepo();

        void addPaper(Papers *paper);
        void removePaper(int id);
        void transfer(unsigned id, LibrRepo &other);

        unsigned getSize() const { return size; }
        unsigned getCopies(std::string &isbn) const;

        void showType(Papers::Type type) const;
        void showAll() const;
        void showDetailedInfo(const std::string &isbn) const;

        void printBook(unsigned idx) const;
        void save(std::ofstream& out) const;

        const Papers* operator[](const std::string &title) const;
        const Papers* operator[](int id) const;
        Papers *operator[](int id);

    private:
        Papers **copyRepo(const LibrRepo &other, unsigned newCapacity);
        void resize();
        void free();

        Papers* factory(std::ifstream &in) const;

    private:
        Papers **repo;
        unsigned size;
        unsigned capacity;
};

#endif
