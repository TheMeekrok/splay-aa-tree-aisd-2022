#include <iostream>
#include <fstream>

#include "splay-tree.h"

using namespace std;

int main() {
    auto *t = new SplayTree<string>();

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

            output << "insert " << key;
            if (t->root->key == key)
                output << " SUCCESSFUL \n";
            else
                output << " FAILED \n";
        }
        else if (action == "erase") {
            input >> key;
            t->erase(key);
        }
    }

    t->print_2D();

    return 0;
}
