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
        void showDetailedInfo(const std::string &isbn) const;

        void find(const std::string& option, const std::string &value, Papers::Type type,
                       bool sorted = false, bool asc = true, const std::string &key = "", int top = -1);

        void printBook(unsigned idx) const;
        void save(std::ofstream& out) const;

        const Papers* operator[](const std::string &title) const;
        const Papers* operator[](int id) const;
        Papers *operator[](int id);

    private:
        Papers **copyRepo(const LibrRepo &other, unsigned newCapacity);
        void sort(std::vector<Papers*>& holder, 
                  bool (*compare)(const Papers*, const Papers*, const std::string& value),
                  const std::string& value, bool asc = true);
        bool findHelper(const std::string &option, const std::string &value, unsigned idx);
        void resize();
        void free();

        Papers* factory(std::ifstream &in) const;

    private:
        Papers **repo;
        unsigned size;
        unsigned capacity;
};

#endif
