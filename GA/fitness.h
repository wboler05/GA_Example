#ifndef FITNESS_H
#define FITNESS_H

#include <vector>
#include <limits>

class Fitness
{
public:

    static double realFunctionToEmulate(const double & x);
    static double function(const std::vector<double> & state, const double & x);

    static int coeffs() { return m_coeffs; }
    static const std::vector<double> & realCoeffs() { return m_real_coeffs; }

private:
    Fitness()=delete;

    static int m_coeffs;
    static std::vector<double> m_real_coeffs;

};

#endif // FITNESS_H
