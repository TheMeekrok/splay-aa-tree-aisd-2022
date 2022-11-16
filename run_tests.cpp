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

#define TESTS 25
#define INSERT_UNIT 6
#define ERASE_UNIT 11
#define RANDOM_ACCESS_UNIT 16
#define RECENT_ACCESS_UNIT 21

#define ALLOWABLE_STD_DEVIATION_INC 0.0001
#define MIN_ITERATIONS 10

using namespace std;
using namespace std::chrono;

// Вычисление среднего арифметического
double get_average(vector<double> &operations_time, int N) {
    double average = 0;

    for (double elem: operations_time)
        average += elem;

    return average /= N;
}

// Вычисление среднеквадратичного отклонения
double get_average_deviation(vector<double> &operations_time, int N) {
    double average = get_average(operations_time, N);
    double average_deviation = 0;

    for (double elem: operations_time) 
        average_deviation += pow(elem - average, 2);
    
    return sqrt(average_deviation / N);
}

void run_splay() {
    // Поток для записы выходных данных
    ofstream _log("./docs/splay_log.out");

    for (int test = 1; test <= TESTS; ++test) {

        // Экземпляр splay-дерева
        auto Splay = new SplayTree<string>();

        int passed = 0;

        vector<string> v_elements;
        bool is_passed = true;

        // Логирование
        if (test == INSERT_UNIT)
            _log << "INSERT_UNIT\n";

        else if (test == ERASE_UNIT)
            _log << "ERASE_UNIT\n";

        else if (test == RANDOM_ACCESS_UNIT)
            _log << "RANDOM_ACCESS_UNIT\n";
        
        else if (test == RECENT_ACCESS_UNIT)
            _log << "RECENT_ACCESS_UNIT \n";

        // Время начала теста
        auto start = high_resolution_clock::now();
 
        // Блоки тестирования с использованием генератора
        if (test >= RECENT_ACCESS_UNIT) {
            const int N = (int)pow(10, test - RECENT_ACCESS_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                Splay->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Поиск недавнего элемента (случайного из N / 10
            // последних добавленных)
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC 
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                int index = random_int(N - (N / 10), N);

                Splay->access(v_elements[index]);
                operations_time.push_back(Splay->get_access_ops());

                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        else if (test >= RANDOM_ACCESS_UNIT) {
            const int N = (int)pow(10, test - RANDOM_ACCESS_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                Splay->insert(key);
                v_elements.push_back(key);
            }

            // Поиск полностью случайного элемента
            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC 
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                int index = random_int(0, N);

                Splay->access(v_elements[index]);
                operations_time.push_back(Splay->get_access_ops());

                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        else if (test >= ERASE_UNIT) {
            const int N = (int)pow(10, test - ERASE_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                Splay->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Удаление случайного элемента
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                Splay->erase(v_elements[random_int(0, N)]);

                // За удалением 1 элемента следует вставка 1 элемента
                string key = next_rnd_string();
                Splay->insert(key);

                v_elements.push_back(key);

                operations_time.push_back(Splay->get_erase_ops());
                size = operations_time.size();

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }
            
        else if (test >= INSERT_UNIT) {
            const int N = (int)pow(10, test - INSERT_UNIT + 1);

            // Вставка N - 1 полностью случайных элементов
            for (int i = 0; i < N - 1; ++i) {
                string key = next_rnd_string();
                Splay->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Вставка N-ного элемента
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                string key = next_rnd_string();
                Splay->insert(key);
                Splay->erase(key);
                v_elements.push_back(key);

                operations_time.push_back(Splay->get_insert_ops());
                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        // Ручные тесты на корректность
        else {
            // Потоки ввода/вывода
            ifstream input("./tests/" + to_string(test) + INPUT_F);
            ofstream output("./tests/" + to_string(test) + OUTPUT_F);
            ifstream answer("./tests/" + to_string(test) + ANSWER_F);

            // Считывание команды и выполнение её
            string command;
            while (input >> command) {
                string key;
                bool ans;

                // Вставка
                if (command == "i") {
                    input >> key;
                    Splay->insert(key);

                    v_elements.push_back(key);
                }

                // Получение доступа
                else if (command == "a") {
                    input >> key;
                    bool result = Splay->access(key);
                    output << result << "\n";
                    answer >> ans;

                    if (ans != result) 
                        is_passed = false;
                }

                // Удаление
                else if (command == "e") {
                    input >> key;
                    Splay->erase(key);
                }
            }
        }

        // Время конца теста
        auto stop = high_resolution_clock::now();
        auto execution_time = duration_cast<microseconds>(stop - start);

        // removing duplicates in array
        std::sort(v_elements.begin(), v_elements.end());
        auto last = unique(v_elements.begin(), v_elements.end());
        v_elements.erase(last, v_elements.end());

        std::cout << "Test " << test
            << ((is_passed) ? "" : " not") << " passed. \n" 
            << "Total elements (n): " << v_elements.size() << "\n"
            << "Total operations per last: \n"
            << "- insert: " << Splay->get_insert_ops() << "\n"
            << "- access: " << Splay->get_access_ops() << "\n"
            << "- erase: " << Splay->get_erase_ops() << "\n"
            << "Execution time (ms): " 
            << (double)execution_time.count() / 1000 << "\n"
            << "-----------------" << endl;

        delete Splay;
    }
}

void run_aa() {
    // Поток для записы выходных данных
    ofstream _log("./docs/aa_log.out");

    for (int test = 1; test <= TESTS; ++test) {

        // Экземпляр AA-дерева
        auto AA = new AATree<string>();

        int passed = 0;

        vector<string> v_elements;
        bool is_passed = true;

        // Логирование
        if (test == INSERT_UNIT)
            _log << "INSERT_UNIT\n";

        else if (test == ERASE_UNIT)
            _log << "ERASE_UNIT\n";

        else if (test == RANDOM_ACCESS_UNIT)
            _log << "RANDOM_ACCESS_UNIT\n";
        
        else if (test == RECENT_ACCESS_UNIT)
            _log << "RECENT_ACCESS_UNIT \n";

        // Время начала теста
        auto start = high_resolution_clock::now();
 
        // Блоки тестирования с использованием генератора
        if (test >= RECENT_ACCESS_UNIT) {
            const int N = (int)pow(10, test - RECENT_ACCESS_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                AA->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Поиск недавнего элемента (случайного из N / 10
            // последних добавленных)
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC 
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                int index = random_int(N - (N / 10), N);

                AA->access(v_elements[index]);
                operations_time.push_back(AA->get_access_ops());

                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        else if (test >= RANDOM_ACCESS_UNIT) {
            const int N = (int)pow(10, test - RANDOM_ACCESS_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                AA->insert(key);
                v_elements.push_back(key);
            }

            // Поиск полностью случайного элемента
            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC 
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                int index = random_int(0, N);

                AA->access(v_elements[index]);
                operations_time.push_back(AA->get_access_ops());

                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        else if (test >= ERASE_UNIT) {
            const int N = (int)pow(10, test - ERASE_UNIT + 1);

            // Вставка N полностью случайных элементов
            for (int i = 0; i < N; ++i) {
                string key = next_rnd_string();
                AA->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Удаление случайного элемента
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                AA->erase(v_elements[random_int(0, N)]);

                // За удалением 1 элемента следует вставка 1 элемента
                string key = next_rnd_string();
                AA->insert(key);

                v_elements.push_back(key);

                operations_time.push_back(AA->get_erase_ops());
                size = operations_time.size();

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }
            
        else if (test >= INSERT_UNIT) {
            const int N = (int)pow(10, test - INSERT_UNIT + 1);

            // Вставка N - 1 полностью случайных элементов
            for (int i = 0; i < N - 1; ++i) {
                string key = next_rnd_string();
                AA->insert(key);
                v_elements.push_back(key);
            }

            vector<double> operations_time;
            size_t size = 0;

            double prev_average_deviation = 1, average_deviation = 0;
            int iter = 0;

            // Вставка N-ного элемента
            // Тесты продолжаются, пока приращение среднеквадратичного 
            // отклонения не будет меньше, чем ALLOWABLE_STD_DEVIATION_INC
            while (abs(prev_average_deviation - 
                average_deviation) > ALLOWABLE_STD_DEVIATION_INC
                || iter < MIN_ITERATIONS) {

                prev_average_deviation = average_deviation;

                string key = next_rnd_string();
                AA->insert(key);
                AA->erase(key);
                v_elements.push_back(key);

                operations_time.push_back(AA->get_insert_ops());
                size = operations_time.size();

                average_deviation = get_average_deviation(operations_time, size);

                iter++;
            }

            _log << N << " " << get_average(operations_time, size) << "\n";
        }

        // Ручные тесты на корректность
        else {
            // Потоки ввода/вывода
            ifstream input("./tests/" + to_string(test) + INPUT_F);
            ofstream output("./tests/" + to_string(test) + OUTPUT_F);
            ifstream answer("./tests/" + to_string(test) + ANSWER_F);

            // Считывание команды и выполнение её
            string command;
            while (input >> command) {
                string key;
                bool ans;

                // Вставка
                if (command == "i") {
                    input >> key;
                    AA->insert(key);

                    v_elements.push_back(key);
                }

                // Получение доступа
                else if (command == "a") {
                    input >> key;
                    bool result = AA->access(key);
                    output << result << "\n";
                    answer >> ans;

                    if (ans != result) 
                        is_passed = false;
                }

                // Удаление
                else if (command == "e") {
                    input >> key;
                    AA->erase(key);
                }
            }
        }

        // Время конца теста
        auto stop = high_resolution_clock::now();
        auto execution_time = duration_cast<microseconds>(stop - start);

        // removing duplicates in array
        std::sort(v_elements.begin(), v_elements.end());
        auto last = unique(v_elements.begin(), v_elements.end());
        v_elements.erase(last, v_elements.end());

        std::cout << "Test " << test
            << ((is_passed) ? "" : " not") << " passed. \n" 
            << "Total elements (n): " << v_elements.size() << "\n"
            << "Total operations per last: \n"
            << "- insert: " << AA->get_insert_ops() << "\n"
            << "- access: " << AA->get_access_ops() << "\n"
            << "- erase: " << AA->get_erase_ops() << "\n"
            << "Execution time (ms): " 
            << (double)execution_time.count() / 1000 << "\n"
            << "-----------------" << endl;

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

    if (strcmp(argc[1], "splay") == 0) {
        run_splay();
    }

    return 0;
}