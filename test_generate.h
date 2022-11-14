#include <string>
#include <ctime>
#include <random>

#define STRING_LENGTH 1000
#define MAGIC_CONST 0xACE5423FFFCEDD

using namespace std;

const int l_bound = 33;
const int r_bound = 126;

random_device r;
default_random_engine e1(r());

int random_int(int l_bound, int r_bound) {
    uniform_int_distribution<int> uniform_dist(l_bound, r_bound - 1);
    return uniform_dist(e1);
}

string next_psd_rnd_string(int seed_1, int seed_2 = 0) {
    string random = "";
    
    for (int i = 0; i < STRING_LENGTH; ++i) {
        uint64_t seed = (uint64_t(seed_1 * seed_2) ^ MAGIC_CONST) << i;
    
        srand(seed);
        int pos = rand() % (r_bound - l_bound) + l_bound;
        random += char(pos);
    }

    return random;
}

string next_rnd_string() {
    string random = "";

    for (int i = 0; i < STRING_LENGTH; ++i) {
        random += char(random_int(l_bound, r_bound));
    }

    return random;
}