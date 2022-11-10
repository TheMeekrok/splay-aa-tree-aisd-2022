#include <iostream>
#include <fstream>
#include <cstring>

#include <set>

#include "splay-tree.h"
#include "aa-tree.h"

#define INPUT_F ".in"
#define OUTPUT_F ".out"
#define ANSWER_F ".ans"

#define TESTS 5

using namespace std;

void run_aa_tree() {
    int passed = 0;

    for (int test = 1; test <= TESTS; ++test) {
        // AA-tree instance
        auto AA = new AATree<string>();

        // register testing directory
        ifstream input("./tests/" + to_string(test) + INPUT_F);
        ofstream output("./tests/" + to_string(test) + OUTPUT_F);
        ifstream answer("./tests/" + to_string(test) + ANSWER_F);

        bool is_passed = true;
        uint64_t commands = 0;
        set<string> elements;

        // execute test-file
        string command;
        while (input >> command) {
            string key;
            bool ans;
            // insert
            if (command == "i") {
                input >> key;
                AA->insert(key);

                elements.insert(key);
                commands++;
            }
            // access
            else if (command == "a") {
                input >> key;
                bool result = AA->access(key);
                output << result << "\n";
                answer >> ans;

                if (ans != result) 
                    is_passed = false;

                commands++;
            }
            // erase
            else if (command == "e") {
                input >> key;
                AA->erase(key);

                commands++;
            }
        }

        cout << "Test " << test
            << ((is_passed) ? "" : " not") << " passed. \n" 
            << "Total commands: " << commands << "\n"
            << "Total elements (n): " << elements.size() << "\n"
            << "Total operations: \n"
            << "- per inserting: " << AA->get_insert_ops() << "\n"
            << "- per accessing: " << AA->get_access_ops() << "\n"
            << "- per erasing: " << AA->get_erase_ops() << "\n"
            << "-----------------" << endl;

        delete AA;
    }
}

int main(int argv, char* argc[]) {
    if (argv < 2) {
        return 0;
    }
    else {
        ios_base::sync_with_stdio(false);

        if (strcmp(argc[1], "aa") == 0) {
            run_aa_tree();
        }
    }


}