#ifndef SPLAY_AA_TREE_TESTER_H
#define SPLAY_AA_TREE_TESTER_H

#include <ctime>
#include <chrono>
#include "splay-tree.h"
#include "aa-tree.h"

void run_tests(std::string input_file, std::string output_file, std::string answer_file) {
    auto *S = new SplayTree<int>();
    auto *AA = new AATree<int>();

    std::ifstream input(input_file);
    std::ofstream output(output_file);
    std::ifstream answer(answer_file);

    std::string input_string;

    auto start = std::chrono::high_resolution_clock::now();

    while (input >> input_string) {
        int key;

        if (input_string == "insert") {
            input >> key;
            S->insert(key);
        }
        else if (input_string == "access") {
            input >> key;
            S->access(key);
            //output << "Key " << key << (S->access(key) ? " found\n" : " not found\n");
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    output << "Splay Tree execution time (ms): " << double(duration.count()) / 1000 << "\n";

    input.close();
    input.open(input_file);
    input.seekg(0);

    start = std::chrono::high_resolution_clock::now();

    while (input >> input_string) {
        int key;

        if (input_string == "insert") {
            input >> key;
            AA->insert(key);
        }
        else if (input_string == "access") {
            input >> key;
            AA->access(key);
            //output << "Key " << key << (AA->access(key) ? " found\n" : " not found\n");
        }
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    output << "AA Tree execution time (ms): " << double(duration.count()) / 1000 << "\n";
}

#endif //SPLAY_AA_TREE_TESTER_H
