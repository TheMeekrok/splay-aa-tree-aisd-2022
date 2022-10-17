#include <iostream>
#include <fstream>

#include "splay-tree.h"
#include "aa-tree.h"

using namespace std;

int main() {
    auto *t = new AATree<string>();

    ifstream input("test03.txt");
    ofstream output("output.txt");

    string action;
    while (input >> action) {
        string key;
        bool expected;
        if (action == "access") {
            input >> key >> expected;

            output << "access " << key;
            if (t->access(key))
                output << " RESULT: " << key << "\n";
            else
                output << " NOT FOUND \n";
        }
        else if (action == "insert") {
            input >> key;
            t->insert(key);

            output << "insert " << key << "\n";
//            if (t->root->key == key)
//                output << " SUCCESSFUL \n";
//            else
//                output << " FAILED \n";
        }
        else if (action == "erase") {
            input >> key;
            t->erase(key);
        }
    }

    t->print_2D();

//    auto *aa = new AATree<int>();
//    aa->insert(8);
//    aa->insert(4);
//    aa->insert(12);
//    aa->insert(2);
//    aa->insert(10);
//    aa->insert(16);
//    aa->insert(100);
//
//    aa->root = aa->_erase(8, aa->root);
//
//    aa->insert(0);
//    aa->insert(1);
//
//    aa->root = aa->_erase(4, aa->root);
//
//
//
//    aa->print_2D();

    return 0;
}
