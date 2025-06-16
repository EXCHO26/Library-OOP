#include "Service/LibrService.hpp"

int main()
{

    std::ofstream books("papers.dat", std::ios::binary);
    Book b("Moqta purva kniga", "Bard", "Kniga bez ime", "12345", 2025, 9.0, "Drama", {"ala"});
    b.saveOnFile(books);

    std::ifstream books1("papers.dat", std::ios::binary);
    std::ifstream taken1("taken.dat", std::ios::binary);
    std::ifstream users1("users.dat", std::ios::binary);

    LibrService ser(books1, taken1, users1);

    if (ser.login("admin", "i<3c++")) std::cout << "User logged!" << '\n';
    ser.addBook(new Book("Moqta purva kniga", "Bard", "Kniga bez ime", "12345", 2025, 9.0, "Drama", {"ala"}));
    ser.addBook(new Periodical("Periodichno", "drug", "alabala", "123", 1223, 3.4, "Drama", 3, 1, {}));

    ser.addUser(new Reader("Krasi", "123456"));
    ser.logout();
    ser.login("Krasi", "123456");

    ser.take(1);
    ser.give(1);

    ser.showAll();

    std::cout << "All good!" << std::endl;
}
