#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

#include <random>
#include <chrono>

class RandomNumber
{
public:
    static std::default_random_engine engine;

    static void seed();
    static void seed(size_t s);

    static int uniformInt(const int & low, const int & high);
    static double uniformReal(const double & low, const double & high);

private:
    RandomNumber()=delete;
};

#endif // RANDOMNUMBER_H
