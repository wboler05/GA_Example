#include "fitness.h"

#include <QDebug>

int Fitness::m_coeffs=3;
std::vector<double> Fitness::m_real_coeffs = {2.0, 0.5, -1.0};

double Fitness::realFunctionToEmulate(const double & x) {
    std::vector<double> coeffs = {2, 0.5, -1};
    return function(coeffs, x);

    //return (2.0 * x * x) + (0.5 * x) - 1;
}

double Fitness::function(const std::vector<double> & state, const double & x) {
    if (state.size() != m_coeffs) {
        qDebug() << "Error, state size does not match coefficient size.";
        return std::numeric_limits<double>::signaling_NaN();
    } else {
        double additive_buffer = 0; // f(x) = ax^N + bx^N-1 + .... + yx^1 + z
        for (int i = 0; i < m_coeffs; i++) {
            double mult_buffer = state[i];
            for (int j = 0; j < m_coeffs - i - 1; j++) {
                mult_buffer *= x;
            }
            additive_buffer += mult_buffer;
        }
        return additive_buffer;
    }
}
