#include "Map.hpp"
#include "print_tree.hpp"

int main(void)
{
    ft::Map<std::string, int > ap;
    ft::Map<int, int > ape;

    ape.insert(ft::pair<const int, int> (14, 666));
    ape.insert(ft::pair<const int, int> (17, 666));
    ape.insert(ft::pair<const int, int> (11, 666));
    ape.insert(ft::pair<const int, int> (7, 666));
    ape.insert(ft::pair<const int, int> (53, 666));
    ft::printLevelOrder(ape._root);
     ape.insert(ft::pair<const int, int> (4, 666));
    ft::printLevelOrder(ape._root);
    ape.insert(ft::pair<const int, int> (13, 666));
    ape.insert(ft::pair<const int, int> (12, 666));
    ft::printLevelOrder(ape._root);
     ape.insert(ft::pair<const int, int> (8, 666));
     ape.insert(ft::pair<const int, int> (60, 666));
    ft::printLevelOrder(ape._root);
     ape.insert(ft::pair<const int, int> (19, 666));
     ape.insert(ft::pair<const int, int> (16, 666));
     ape.insert(ft::pair<const int, int> (20, 666));
     ft::printLevelOrder(ape._root);


    ape.deletes(ape._root, 8);
    ape.deletes(ape._root, 7);
    ape.deletes(ape._root, 11);
    ft::printLevelOrder(ape._root);
    ape.deletes(ape._root, 14);
    ape.deletes(ape._root, 17);
    ft::printLevelOrder(ape._root);

    // ap.insert(ft::pair<const std::string, int> ("Caba", 666));
    // ap.insert(ft::pair<const std::string, int> ("Baba", 777));
    //  ft::printLevelOrder(ap._root);
    // ap.insert(ft::pair<const std::string, int> ("Aba", 555));
    // ap.insert(ft::pair<const std::string, int> ("Aba", 555));
    //  ft::printLevelOrder(ap._root);
    // ap.insert(ft::pair<const std::string, int> ("Bba", 555));
    // ft::printLevelOrder(ap._root);
    
    // ft::Map<std::string, int > ap1;

    // ap1.insert(ft::pair<const std::string, int> ("Cibi", 666));
    // //ap1.insert(ft::pair<const std::string, int> ("Baba", 777));
    // //ap1.insert(ft::pair<const std::string, int> ("Saba", 555));
    // ap1.insert(ft::pair<const std::string, int> ("Eigi", 555));
    //  ft::printLevelOrder(ap1._root);
    // ap1.insert(ft::pair<const std::string, int> ("Dibi", 555));
    // ft::printLevelOrder(ap1._root);


    // ap.insert(ft::pair<const std::string, int> ("Daba", 555));
    // ap.insert(ft::pair<const std::string, int> ("Baa", 555));
    // ap.insert(ft::pair<const std::string, int> ("Zizi", 555));
    //  ft::printLevelOrder(ap._root);
    // ap.insert(ft::pair<const std::string, int> ("Xac", 555));
    // ap.insert(ft::pair<const std::string, int> ("Flac", 555));
    //  ft::printLevelOrder(ap._root);
    // //  ap.insert(ft::pair<const std::string, int> ("Aza", 555));
    // //  ap.insert(ft::pair<const std::string, int> ("Akzo", 555));
    //  ap.insert(ft::pair<const std::string, int> ("Plouc", 555));
    //  ft::printLevelOrder(ap._root);
    // ap.insert(ft::pair<const std::string, int> ("Hululu", 555));
    // ap.insert(ft::pair<const std::string, int> ("Zb", 555));
    //  ft::printLevelOrder(ap._root);


    // ap.deletes(ap._root, "fdsa");
    // ap.deletes(ap._root, "PIPI");
    // ap.deletes(ap._root, "Zizi");
    // ap.deletes(ap._root, "Caca");

    //  ft::printLevelOrder(ap._root);
    // std::cout << "AFTER DELETE " << std::endl;
    // ap.insert(ft::pair<const std::string, int> ("Caca", 555));
    // ap.insert(ft::pair<const std::string, int> ("Aba", 555));
    // ap.deletes(ap._root, "PIPI");
    //  std::cout << "AFTER DELETE " << std::endl;
    // ap.deletes(ap._root, "Caca");
    //  std::cout << "AFTER DELETE " << std::endl;
    // ap.deletes(ap._root, "Baba");
    //  std::cout << "AFTER DELETE " << std::endl;
    // ap.deletes(ap._root, "Aba");
    // ap.deletes(ap._root, "Daba");
    
    // ap.deletes(ap._root, "Xac");
    // ap.deletes(ap._root, "Flac");
    // ap.deletes(ap._root, "Aaa");
    // ap.deletes(ap._root, "Plouc");
    // ap.deletes(ap._root, "Level");
    // ap.deletes(ap._root, "Hululu");

    return (0);
}