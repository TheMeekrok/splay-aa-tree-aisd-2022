#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <cmath>
#include <ctime>
#include <algorithm>

#include <set>
#include <vector>

#include "splay-tree.h"
#include "aa-tree.h"
#include "test_generate.h"

#define INPUT_F ".in"
#define OUTPUT_F ".out"
#define ANSWER_F ".ans"

#define TESTS 20
#define PERFORMANCE_UNIT 6
#define RECENT_ELEMENTS_UNIT 11
#define RANDOM_ELEMENTS_UNIT 16

using namespace std;
using namespace std::chrono;

void run_splay() {
    int passed = 0;

    ofstream _log("./docs/log.out");

    for (int test = 1; test <= TESTS; ++test) {
        // Splay-tree instance
        auto Splay = new SplayTree<string>();

        vector<string> v_elements;
        bool is_passed = true;

        // time measurement start point
        auto start = high_resolution_clock::now();
 
        // using generator
        if (test >= RANDOM_ELEMENTS_UNIT) {
            const int N = (int)pow(10, test - RANDOM_ELEMENTS_UNIT + 1);

            // inserting random elements
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();

                Splay->insert(key);

                v_elements.push_back(key);
            }

            // fully random accesing/erasing
            for (int i = 0; i < N; ++i) {
                int index = random_int(0, N);

                Splay->access(v_elements[index]);
                Splay->erase(v_elements[index]);
            }
        }

        else if (test >= RECENT_ELEMENTS_UNIT) {
            const int N = (int)pow(10, test - RECENT_ELEMENTS_UNIT + 1);

            // inserting elements
            for (int i = 0; i < N; ++i) {
                string key = next_psd_rnd_string(N, i);

                Splay->insert(key);

                v_elements.push_back(key);
            }

            // accesing and erasing recent N / 10 elements
            sort(v_elements.begin(), v_elements.end(), greater<>());
        
            for (int i = 0; i < N / 10; ++i) {
                int index = random_int(0, N / 10);

                Splay->access(v_elements[index]);
                Splay->erase(v_elements[index]);
            }
        }

        else if (test >= PERFORMANCE_UNIT) {
            const int N = (int)pow(10, test - PERFORMANCE_UNIT + 1);

            // inserting elements
            for (int i = 0; i < N; ++i) {
                string key = next_psd_rnd_string(N, i);

                Splay->insert(key);

                v_elements.push_back(key);
            }

            // accesing all elements
            for (auto elem: v_elements) {
                Splay->access(elem);
            }

            // erasing average element
            Splay->erase(v_elements[v_elements.size() / 2]);
        }

        // testing via ./tests
        else {
            // register testing directory
            ifstream input("./tests/" + to_string(test) + INPUT_F);
            ofstream output("./tests/" + to_string(test) + OUTPUT_F);
            ifstream answer("./tests/" + to_string(test) + ANSWER_F);

            // execute test-file
            string command;
            while (input >> command) {
                string key;
                bool ans;

                // insert
                if (command == "i") {
                    input >> key;
                    Splay->insert(key);

                    v_elements.push_back(key);
                }

                // access
                else if (command == "a") {
                    input >> key;
                    bool result = Splay->access(key);
                    output << result << "\n";
                    answer >> ans;

                    if (ans != result) 
                        is_passed = false;
                }

                // erase
                else if (command == "e") {
                    input >> key;
                    Splay->erase(key);
                }
            }
        }

        // time measurement stop point
        auto stop = high_resolution_clock::now();
        auto execution_time = duration_cast<microseconds>(stop - start);

        // removing duplicates in array
        std::sort(v_elements.begin(), v_elements.end());
        auto last = unique(v_elements.begin(), v_elements.end());
        v_elements.erase(last, v_elements.end());

        std::cout << "Test " << test
            << ((is_passed) ? "" : " not") << " passed. \n" 
            << "Total elements (n): " << v_elements.size() << "\n"
            << "Total operations: \n"
            << "- per insert: " << Splay->get_insert_ops() << "\n"
            << "- per access: " << Splay->get_access_ops() << "\n"
            << "- per all accesses: " << Splay->get_access_ops_t() << "\n"
            << "- per erase: " << Splay->get_erase_ops() << "\n"
            << "Execution time (ms): " 
            << (double)execution_time.count() / 1000 << "\n"
            << "-----------------" << endl;

        if (test == PERFORMANCE_UNIT)
            _log << "ACCESS ALL ELEMENTS\n";

        if (test == RECENT_ELEMENTS_UNIT)
            _log << "ACCESS/ERASE RECENT ELEMENTS\n";

        if (test == RANDOM_ELEMENTS_UNIT)
            _log << "ACCESS/ERASE RANDOM ELEMENTS\n";

        // logging
        if (test >= PERFORMANCE_UNIT) {
            _log << v_elements.size() << " "
                << Splay->get_insert_ops() << " "
                << Splay->get_access_ops() << " " 
                << Splay->get_access_ops_t() << " "
                << Splay->get_erase_ops() << "\n";
        }

        delete Splay;
    }
}

void run_aa() {
    int passed = 0;

    ofstream _log("./docs/log.out");

    for (int test = 1; test <= TESTS; ++test) {
        // AA-tree instance
        auto AA = new AATree<string>();

        vector<string> v_elements;
        bool is_passed = true;

        // time measurement start point
        auto start = high_resolution_clock::now();
 
        // using generator
        if (test >= RANDOM_ELEMENTS_UNIT) {
            const int N = (int)pow(10, test - RANDOM_ELEMENTS_UNIT + 1);

            // inserting elements
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();

                AA->insert(key);

                v_elements.push_back(key);
            }

            // fully random accesing/erasing
            for (int i = 0; i < N; ++i) {
                int index = random_int(0, N);

                AA->access(v_elements[index]);
                AA->erase(v_elements[index]);
            }
        }

        else if (test >= RECENT_ELEMENTS_UNIT) {
            const int N = (int)pow(10, test - RECENT_ELEMENTS_UNIT + 1);

            // inserting elements
            for (int i = 0; i < N; ++i) {
                string key = next_psd_rnd_string(N, i);

                AA->insert(key);

                v_elements.push_back(key);
            }

            // accesing and erasing recent N / 10 elements
            sort(v_elements.begin(), v_elements.end(), greater<>());
        
            for (int i = 0; i < N / 10; ++i) {
                int index = random_int(0, N / 10);

                AA->access(v_elements[index]);
                AA->erase(v_elements[index]);
            }
        }

        else if (test >= PERFORMANCE_UNIT) {
            const int N = (int)pow(10, test - PERFORMANCE_UNIT + 1);

            // inserting elements
            for (int i = 0; i < N; ++i) {
                string key = next_psd_rnd_string(N, i);

                AA->insert(key);

                v_elements.push_back(key);
            }

            // accesing all elements
            for (auto elem: v_elements) {
                AA->access(elem);
            }

            // erasing average element
            AA->erase(v_elements[v_elements.size() / 2]);
        }

        // testing via ./tests
        else {
            // register testing directory
            ifstream input("./tests/" + to_string(test) + INPUT_F);
            ofstream output("./tests/" + to_string(test) + OUTPUT_F);
            ifstream answer("./tests/" + to_string(test) + ANSWER_F);

            // execute test-file
            string command;
            while (input >> command) {
                string key;
                bool ans;

                // insert
                if (command == "i") {
                    input >> key;
                    AA->insert(key);

                    v_elements.push_back(key);
                }

                // access
                else if (command == "a") {
                    input >> key;
                    bool result = AA->access(key);
                    output << result << "\n";
                    answer >> ans;

                    if (ans != result) 
                        is_passed = false;
                }

                // erase
                else if (command == "e") {
                    input >> key;
                    AA->erase(key);
                }
            }
        }

        // time measurement stop point
        auto stop = high_resolution_clock::now();
        auto execution_time = duration_cast<microseconds>(stop - start);

        // removing duplicates in array
        std::sort(v_elements.begin(), v_elements.end());
        auto last = unique(v_elements.begin(), v_elements.end());
        v_elements.erase(last, v_elements.end());

        std::cout << "Test " << test
            << ((is_passed) ? "" : " not") << " passed. \n" 
            << "Total elements (n): " << v_elements.size() << "\n"
            << "Total operations: \n"
            << "- per insert: " << AA->get_insert_ops() << "\n"
            << "- per access: " << AA->get_access_ops() << "\n"
            << "- per all accesses: " << AA->get_access_ops_t() << "\n"
            << "- per erase: " << AA->get_erase_ops() << "\n"
            << "Execution time (ms): " 
            << (double)execution_time.count() / 1000 << "\n"
            << "-----------------" << endl;

        if (test == PERFORMANCE_UNIT)
            _log << "ACCESS ALL ELEMENTS\n";

        if (test == RECENT_ELEMENTS_UNIT)
            _log << "ACCESS/ERASE RECENT ELEMENTS\n";

        if (test == RANDOM_ELEMENTS_UNIT)
            _log << "ACCESS/ERASE RANDOM ELEMENTS\n";

        // logging
        if (test >= PERFORMANCE_UNIT) {
            _log << v_elements.size() << " "
                << AA->get_insert_ops() << " "
                << AA->get_access_ops() << " " 
                << AA->get_access_ops_t() << " "
                << AA->get_erase_ops() << "\n";
        }

        delete AA;
    }
}

int main(int argv, char* argc[]) {
    if (argv < 2) {
        return 0;
    }

    ios_base::sync_with_stdio(false);

    if (strcmp(argc[1], "aa") == 0) {
        run_aa();
    }
    else if (strcmp(argc[1], "splay") == 0) {
        run_splay();
    }

    return 0;
}