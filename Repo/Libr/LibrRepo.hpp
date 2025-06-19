#ifndef LIBR_REPO_HEADER
#define LIBR_REPO_HEADER

#include <cmath>

#include "Units/Series.hpp"

/// @brief Manages a dynamic repository of Papers (Books, Periodicals, Series).
class LibrRepo
{
    public:
        /// @brief Default constructor. Initializes an empty repository.
        LibrRepo();

        /// @brief Constructs a repository from file input.
        /// @param in Input file stream.
        LibrRepo(std::ifstream& in);

        /// @brief Copy constructor.
        /// @param other LibrRepo to be copied.
        LibrRepo(const LibrRepo &other);

        /// @brief Assignment operator.
        /// @param other LibrRepo to be assign from
        /// @return Reference to this object.
        LibrRepo &operator=(const LibrRepo &other);

        /// @brief Destructor.
        ~LibrRepo();

        /// @brief Adds a new paper to the repository.
        /// @param paper Pointer to the Papers object.
        void addPaper(Papers *paper);

        /// @brief Removes a paper by its ID.
        /// @param id Unique paper ID.
        void removePaper(int id);

        /// @brief Transfers a paper to another repository.
        /// @param id Paper ID to transfer.
        /// @param other Target repository.
        void transfer(unsigned id, LibrRepo &other);

        /// @brief Returns the number of items in the repository.
        /// @return Number of papers.
        unsigned getSize() const { return size; }

        /// @brief Counts the number of copies of a paper by ISBN.
        /// @param isbn The ISBN of the paper.
        /// @return Number of copies.
        unsigned getCopies(std::string &isbn) const;

        /// @brief Displays all papers of a specific type.
        /// @param type The type of paper (BOOK, PERIODICAL, etc.).
        void showType(Papers::Type type) const;

        /// @brief Shows detailed information about a paper using its ISBN.
        /// @param isbn The ISBN of the paper.
        void showDetailedInfo(const std::string &isbn) const;

        /// @brief Finds papers matching certain criteria.
        /// @param option Attribute to search by (e.g., title, author).
        /// @param value Search value.
        /// @param type Paper type to filter.
        /// @param sorted Whether to sort the results.
        /// @param asc Sort in ascending (true) or descending (false) order.
        /// @param key Sort key.
        /// @param top Limit of top results (-1 for no limit).
        void find(const std::string& option, const std::string &value, Papers::Type type,
                       bool sorted = false, bool asc = true, const std::string &key = "", int top = -1);

        /// @brief Prints brief info about a book by its index.
        /// @param idx Index in the repository.
        void printBook(unsigned idx) const;

        /// @brief Saves the repository to a file.
        /// @param out Output file stream.
        void save(std::ofstream& out) const;

        /// @brief Gets a paper by its title (read-only).
        /// @param title Title of the paper.
        /// @return Pointer to the paper (or nullptr).
        const Papers* operator[](const std::string &title) const;

        /// @brief Gets a paper by its ID (read-only).
        /// @param id ID of the paper.
        /// @return Pointer to the paper (or nullptr).
        const Papers* operator[](int id) const;

        /// @brief Gets a modifiable paper by ID.
        /// @param id id ID of the paper.
        /// @return Pointer to the paper (or nullptr).
        Papers *operator[](int id);

    private:
        /// @brief Helper to copy the repository's contents.
        /// @param other Repository to copy from.
        /// @param newCapacity Capacity of the new array.
        /// @return New Papers array.
        Papers **copyRepo(const LibrRepo &other, unsigned newCapacity);

        /// @brief Sorts a vector of papers using a custom comparator.
        /// @param holder 
        /// @param compare 
        /// @param value 
        /// @param asc 
        void sort(std::vector<Papers*>& holder, 
                  bool (*compare)(const Papers*, const Papers*, const std::string& value),
                  const std::string& value, bool asc = true);

        /// @brief Internal helper for search filtering.
        /// @param option 
        /// @param value 
        /// @param idx 
        /// @return 
        bool findHelper(const std::string &option, const std::string &value, unsigned idx);

        /// @brief Resizes the internal repository array.
        void resize();

        /// @brief Frees memory used by the repository.
        void free();

        /// @brief Factory method that constructs a Papers object from a file.
        /// @param in Input file stream.
        /// @return Pointer to a new Papers object.
        Papers* factory(std::ifstream &in) const;

    private:
        Papers **repo;          ///< Dynamic array of pointers to Papers
        unsigned size;          ///< Number of current papers
        unsigned capacity;      ///< Allocated capacity of the array
};

#endif
