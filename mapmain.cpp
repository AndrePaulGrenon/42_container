#include "Map.hpp"
#include "print_tree.hpp"
#include <map>
#include <iterator>

int main(void)
{
    ft::Map<std::string, int > ap;
    ft::Map<int, int > ape;

    ape.insert(ft::pair<const int, int> (10, 666));

    ape.insert(ft::pair<const int, int> (5, 666));
    ape.insert(ft::pair<const int, int> (50, 777));
    ape.insert(ft::pair<const int, int> (-5, 123));
    ft::printLevelOrder(ape._root);
    ape.insert(ft::pair<const int, int> (-30, 123));
    ape.insert(ft::pair<const int, int> (30, 123));
    ape.insert(ft::pair<const int, int> (70, 123));
    ape.insert(ft::pair<const int, int> (-40, 123));
    ape.insert(ft::pair<const int, int> ( -20, 123));
    ape.insert(ft::pair<const int, int> (33, 123));
    ape.insert(ft::pair<const int, int> (37, 123));
    ape.insert(ft::pair<const int, int> (78, 123));
    ape.insert(ft::pair<const int, int> (-41, 123));
    ape.insert(ft::pair<const int, int> ( -22, 123));
    ape.insert(ft::pair<const int, int> (15, 123));
    ape.insert(ft::pair<const int, int> (50, 123));
    ape.insert(ft::pair<const int, int> (40, 123));
    ape.insert(ft::pair<const int, int> (-45, 123));
    ape.insert(ft::pair<const int, int> (-15, 123));
    ape.insert(ft::pair<const int, int> (55, 123));
    ape.insert(ft::pair<const int, int> (75, 123));
    ape.insert(ft::pair<const int, int> (-47, 123));
    ape.insert(ft::pair<const int, int> (-42, 123));


    //TEST ITERATORS WITH ERASE
    
    // for (size_t i = 100; i > 0; i--)
    // {
    //    ape.insert(ft::pair<const int, int> (i, 123));
    // }
    ft::printLevelOrder(ape._root);

    std::cout << BRED << "IS 3 found ? : " CLEAR << ape.count(10) << std::endl;
    std::cout << BRED << "IS 69 found ? : " CLEAR << ape.count(55) << std::endl;
    std::cout << BRED << "IS -77 found ? : " CLEAR << ape.count(-77) << std::endl;
    
    ft::Map<int, int>::iterator it = ape.lower_bound(36);

    std::cout << "  Number: " << (*it).first ;
    it = ape.upper_bounds(40);
    std::cout << "  Number: " << (*it).first << std::endl ;

    ft::pair<ft::Map<int, int>::iterator, ft::Map<int, int>::iterator> a;

    a = ape.equal_range(5);

    std::cout << " Equal range: " << (*a.second).first << std::endl;


    // ft::Map<int, int>::iterator it = ape.begin();
    // for (size_t i = 0; i < 20; i++)
    // {
    //     it++;
    // }
    // for (size_t i = 0; i < 60; i++)
    // {
    //     std::cout << "  Number; " << (*it).first ;
    //     ape.erase(it);
    //     it++;
    // }
    std::cout << std::endl << std::endl;

    // std::map<int,int> realmap;
    // for (size_t i = 0; i < 100; i++)
    // {
    //     realmap.insert(std::pair<int, int>(i, 123));
    // }
    // std::map<int,int>::iterator realit = realmap.begin();
    // for (size_t i = 0; i < 20; i++)
    // {
    //     realit++;
    // }
    // for (size_t i = 0; i < 70; i++)
    // {
        
    //     std::cout << "  Number; " << (*realit).first ;
    //     realmap.erase(realit);
    //     realit++;
    // }

    // ape.erase(it, ape.end());

    // ape.insert(ft::pair<const int, int> (-42, 123));

    // ft::printLevelOrder(ape._root);
    // ape.erase(13);
    // ape.erase(12);
    // ft::printLevelOrder(ape._root);
    // ape.erase(70);
    // ft::printLevelOrder(ape._root);
    // ape.erase(10);
    // ape.erase(50);
    // ape.erase(75);
    // ape.erase(-40);
    // ape.erase(33);
    // ape.erase(-45);
    // ape.erase(78);
    // ft::printLevelOrder(ape._root);
    // ape.erase(37);
    // ft::printLevelOrder(ape._root);
    // ape.erase(30);
    // ft::printLevelOrder(ape._root);
    // ape.erase(-41);
    // ape.erase(-47);
    // ape.erase(-42);
    // ape.erase(10);
    // ape.insert(ft::pair<const int, int> (55, 123));
    // ape.insert(ft::pair<const int, int> (45, 123));
    // ape.insert(ft::pair<const int, int> (39, 123));
    // ape.insert(ft::pair<const int, int> (9 , 123));
    // ape.insert(ft::pair<const int, int> (23, 123));
    // ape.insert(ft::pair<const int, int> (43, 123));
    // ape.insert(ft::pair<const int, int> (17, 123));
    // ape.insert(ft::pair<const int, int> (8 , 123));
    // ft::printLevelOrder(ape._root);
   
    // ape.insert(ft::pair<const int, int> (69 , 123));
    // ape.insert(ft::pair<const int, int> (99 , 123));
    // ape.insert(ft::pair<const int, int> (666 , 123));
    // ape.erase(45);
    // ape.erase(23);
    // ft::printLevelOrder(ape._root);
    // ape.erase(10);
    // // ft::printLevelOrder(ape._root);
    // ape.erase(40);
    // // ft::printLevelOrder(ape._root);
    // ape.erase(38);

    

    // ape.insert(ft::pair<const int, int> (10, 123));
    // ft::printLevelOrder(ape._root);

    // ape.erase(1);
    // // ft::printLevelOrder(ape._root);

    // ape.erase(30);

    // ape.erase(40);
    // ft::printLevelOrder(ape._root);
    //  ape.erase(-20);
    // ft::printLevelOrder(ape._root);
    //  ape.erase(55);
    //  ape.erase(-47);
    // ft::printLevelOrder(ape._root);
    //  ape.erase(75);
    //INSERT RB TREE
    // ape.insert(ft::pair<const int, int> (2, 666));
    // ape.insert(ft::pair<const int, int> (23, 666));
    // ape.insert(ft::pair<const int, int> (3, 123));
    // ape.insert(ft::pair<const int, int> (16, 777));
    // ape.insert(ft::pair<const int, int> (13, 777));
    // ape.insert(ft::pair<const int, int> (30, 777));
    // ape.insert(ft::pair<const int, int> (77, 777));
    // ape.insert(ft::pair<const int, int> (88, 777));
    // ape.insert(ft::pair<const int, int> (33, 777));
    // ft::printLevelOrder(ape._root);
    
    // ape.erase(30);
    // ape.erase(1);
    //  ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (35, 777));
    // ape.insert(ft::pair<const int, int> (38, 777));
    //  ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (2, 666));
    // ape.insert(ft::pair<const int, int> (1, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (70, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (40, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (60, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (2, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (1, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (70, 666));
    // ft::printLevelOrder(ape._root);
     
    // END of INSERT in RB TREE
    //AVL TESTING 

    // ape.insert(ft::pair<const int, int> (1, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (2, 666));
    // ape.insert(ft::pair<const int, int> (3, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (4, 666));
    // ape.insert(ft::pair<const int, int> (5, 666));
    // ft::printLevelOrder(ape._root);
    //  ape.insert(ft::pair<const int, int> (6, 666));
    // ft::printLevelOrder(ape._root);
    // ape.insert(ft::pair<const int, int> (7, 666));
    // ape.insert(ft::pair<const int, int> (8, 666));
    // ft::printLevelOrder(ape._root);
    //  ape.insert(ft::pair<const int, int> (9, 666));
    //  ape.insert(ft::pair<const int, int> (10, 666));
    // ft::printLevelOrder(ape._root);
    //  ape.insert(ft::pair<const int, int> (11, 666));
    //  ape.insert(ft::pair<const int, int> (12, 666));
    //  ape.insert(ft::pair<const int, int> (13, 666));
    //  ft::printLevelOrder(ape._root);


    // std::cout << MAG<<  ape.erase(13) << CLEAR << std::endl;
    // std::cout << MAG<< ape.erase(69) << CLEAR << std::endl;
    // ape.erase(12);
    // ape.erase(11);
    // ft::printLevelOrder(ape._root);
    // // ape.erase(10);
    // // ft::printLevelOrder(ape._root);
    // ape.erase(9);
    // ft::printLevelOrder(ape._root);

    //AVL TESTING END

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