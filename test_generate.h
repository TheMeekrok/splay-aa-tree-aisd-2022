#ifndef SPLAY_AA_TREE_TEST_GENERATE_H
#define SPLAY_AA_TREE_TEST_GENERATE_H

#include <fstream>
#include <ctime>

void test_generate(std::string output_file, int amount) {
    std::ofstream output(output_file);

    //char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::srand(std::time(nullptr));

    for (int i = 0; i < amount; ++i) {
        int new_num = std::rand() % 2147483646;
        output << "insert " << new_num << "\n";
        output << "access " << new_num << "\n";
    }
}

#endif //SPLAY_AA_TREE_TEST_GENERATE_H
