#ifndef PERIODICAL_HEADER
#define PERIODICAL_HEADER

#include "Papers.hpp"

/// @brief Represents a periodical publication, such as a magazine or journal, derived from Papers.
class Periodical : virtual public Papers
{
    public:
        /// @brief Represents an individual article in a periodical.
        struct Article
        {
            std::string title;                  /**< Title of the article */
            std::string author;                 /**< Author of the article */
            std::vector<std::string> keyWords;  /**< Keywords/tags associated with the article */
        };

        /// @brief Constructs a Periodical from file input.
        /// @param file Input file stream.
        Periodical(std::ifstream& file);

        ///
        /// @brief Constructs a Periodical with given parameters.
        /// 
        /// @param title Title of the periodical.
        /// @param publisher Publisher's name.
        /// @param description Description of the publication.
        /// @param isbn ISBN identifier.
        /// @param yearPublished Year of publication.
        /// @param rating Rating value.
        /// @param genre Genre of the periodical.
        /// @param month Month of the issue.
        /// @param issueNumber Issue number.
        /// @param articles Vector of Article structs contained in the issue.
        Periodical(const std::string &title, const std::string &publisher, const std::string &description,
                   const std::string &isbn, unsigned yearPublished, double rating, 
                   const std::string &genre, unsigned month, unsigned issueNumber,
                   const std::vector<Article> &articles);

        /// @brief Copy constructor.
        /// @param other Periodical object to copy from.
        Periodical(const Periodical &other);

        /// @brief Assignment operator.
        /// @param other Periodical object to assign from.
        /// @return Reference to this object.
        Periodical &operator=(const Periodical &other);

        /// @brief Destructor.
        ~Periodical() {};

        /** @name Accessors */
        ///@{
        unsigned getMonth() const { return month; }
        unsigned getIssueNumber() const { return issueNumber; }
        const std::vector<Article> &getArticles() const { return articles; }
        ///@}

        /** @name Mutators */
        ///@{
        void setIssueNumber(unsigned issueNumber);
        void setMonth(unsigned month);
        void setArticle(const std::vector<Article> &articles);
        ///@}
        
        /// @brief Prints detailed information about the periodical.
        void printInfo() const override;

        /// @brief Saves the periodical data to file.
        /// @param out Output file stream.
        void saveOnFile(std::ofstream &out) const override;

        /// @brief Allows modifying the periodical's attributes.
        void change() override;

        /// @brief Checks whether any article author matches the given string.
        /// @param autor Author name to match.
        /// @return true if match is found, false otherwise.
        bool matchAutor(const std::string &autor) const override;

        /// @brief Checks whether any article keyword matches the given string.
        /// @param taggs Keyword/tag string to match.
        /// @return true if a match is found, false otherwise.
        bool matchTaggs(const std::string &taggs) const override;

        /// @brief Gets the type of paper.
        /// @return Type::PERIODICAL.
        Type getType() const override { return Papers::PERIODICAL; }

        /// @brief Creates a clone of the periodical.
        /// @return Pointer to a new Periodical object.
        Papers *clone() const override;

    protected:
        /// @brief Reads an Article from file.
        /// @param in Input file stream.
        /// @param article Reference to Article struct to fill.
        void readArticle(std::ifstream &in, Article &article);

        /// @brief Writes an Article to file.
        /// @param out Output file stream.
        /// @param articleThe Article to write. 
        void writeArticle(std::ofstream &out, const Article &article) const;

        /// @brief Prints internal details of the periodical (helper).
        void print() const;

        /// @brief Saves internal data of the periodical to file (helper).
        /// @param out Output file stream.
        void save(std::ofstream &out) const;

    private: 
        unsigned month;                 ///< Month of the issue
        unsigned issueNumber;           ///< Issue number
        std::vector<Article> articles;  ///< List of articles in this periodical
};
#endif