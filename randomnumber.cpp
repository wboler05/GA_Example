#include "randomnumber.h"

std::default_random_engine RandomNumber::engine;


void RandomNumber::seed() {
    unsigned s = std::chrono::system_clock::now().time_since_epoch().count();
    seed(s);
}

void RandomNumber::seed(size_t s) {
    engine.seed(s);
}

int RandomNumber::uniformInt(const int & low, const int & high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(engine);
}

double RandomNumber::uniformReal(const double & low, const double & high) {
    std::uniform_real_distribution<double> dist(low, high);
    return dist(engine);
}
