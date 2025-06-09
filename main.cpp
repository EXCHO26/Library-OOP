#include "Papers.hpp"
#include "Book.hpp"
#include "Periodical.hpp"

int main()
{
    Book book("The Great Gatsby", "Scribner", "A novel set in the 1920s", 
                "9780743273565", 1925, 8.5, "Drama", {"American Dream", "Wealth", "Love"});
        
    Book book2("1984", "Secker & Warburg", "A dystopian novel", 
                "9780451524935", 1949, 9.0, "Horror", {"Totalitarianism", "Surveillance", "Freedom"});

    Periodical periodical("Nature", "Nature Publishing Group", "A scientific journal", 
                        "0028-0836", 2023, 9.5, "Mystery", 5, 789, 
                        {{"Quantum Computing Advances", "Alice Smith", {"Quantum", "Computing"}},
                         {"Climate Change Effects", "Bob Johnson", {"Climate", "Change"}}});
    

    std::ofstream out("book.dat", std::ios::binary);
    book.saveOnFile(out);
    book2.saveOnFile(out);
    periodical.saveOnFile(out);
    out.close();

    Papers::Type type;
    std::ifstream in("book.dat", std::ios::binary);
    while (true)
    {
        in.read((char *)&type, sizeof(type));
        if (!in) break;
        switch (type)
        {
        case Papers::BOOK:
            {
                Book bookFromFile(in);
                bookFromFile.printInfo();
            }
            break;
            
        case Papers::PERIODICAL:
            {
                Periodical periodicalFromFile(in);
                periodicalFromFile.printInfo();
            }
        
        default:
            break;
        }
    }
    in.close();
    
    return 0;
}