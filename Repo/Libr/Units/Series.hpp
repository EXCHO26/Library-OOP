#ifndef SERIES_HPP
#define SERIES_HPP

#include "Book.hpp"
#include "Periodical.hpp"

/// @brief Represents a hybrid publication that combines characteristics of both a Book and a Periodical.
class Series : public Book, public Periodical
{
    public:
        /// @brief Constructs a Series object by reading data from a file.
        /// @param file Input file stream to read from.
        Series(std::ifstream& file);

        ///
        /// @brief Constructs a Series with detailed parameters.
        /// @param title Title of the series.
        /// @param publisher Publisher of the series.
        /// @param description Brief description.
        /// @param isbn ISBN code.
        /// @param yearPublished Year of publication.
        /// @param rating Rating score.
        /// @param genre Genre category.
        /// @param month Month of publication.
        /// @param issueNumber Issue number in the series.
        /// @param articles List of articles in the periodical.
        /// @param keyWords Keywords related to the book part.
        /// @param autor Author of the book.
        Series(const std::string &title, const std::string &publisher, const std::string &description,
               const std::string &isbn, unsigned yearPublished, double rating, 
               const std::string &genre, unsigned month, unsigned issueNumber,
               const std::vector<Periodical::Article> &articles,
               const std::vector<std::string>& keyWords,
               const std::string &autor);

        /// @brief Copy constructor.
        /// @param other Series object to copy from.
        Series(const Series &other);

        /// @brief Assignment operator.
        /// @param other Series object to assign from.
        /// @return Reference to this object.
        Series &operator=(const Series &other);

        /// @brief Destructor.
        ~Series() {};

        /// @brief Prints full information about the series.
        void printInfo() const override;

        /// @brief Saves the series information to a file.
        /// @param out Output file stream.
        void saveOnFile(std::ofstream &out) const override;

        /// @brief Checks whether the given author matches the book's author.
        /// @param autor Author name to search.
        /// @return true if match is found.
        bool matchAutor(const std::string &autor) const override;

        /// @brief Checks whether any keyword or article matches the given tag.
        /// @param taggs Tag/keyword to search.
        /// @return true if match is found.
        bool matchTaggs(const std::string &taggs) const override;

        /// @brief Allows editing the series' data fields.
        void change() override;

        /// @brief Returns the specific type identifier. 
        /// @return Papers::SERIES.
        Type getType() const override { return Papers::SERIES; }

        /// @brief Creates a copy of the series object.
        /// @return Pointer to the cloned Series.
        Papers *clone() const override;
    private:
};

#endif