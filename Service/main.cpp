#include "Units/Reader.hpp"
#include "Units/Admin.hpp"
#include "UserRepo.hpp"

int main()
{
    UserRepo repo;

    Reader red("reader1", "qwerty");
    Admin adm("admin1", "qwerty", "krasi@gmail.com");

    repo.addUser(new Reader(red));
    repo.addUser(new Admin(adm));

    std::ofstream rep("repo.dat", std::ios::binary);
    repo.save(rep);
    rep.close();

    std::ifstream rep1("repo.dat", std::ios::binary);
    UserRepo rep2(rep1);

    for (int i = 0; i < rep2.getSize(); i++)
    {
        rep2.printUser(i);
    }
}
