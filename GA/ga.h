#ifndef GA_H
#define GA_H

#include <QDebug>

#include <vector>
#include <cstddef>
#include <cstdlib>
#include <cinttypes>
#include <iostream>

#include "particle.h"
#include "fitness.h"
#include "randomnumber.h"

class GA
{
public:

    struct GA_Params {
        int populationSize = 50;
        double mutationRate = 0.033;
        double crossoverRate = 0.65;
        double terminationCost = 0.0005;
        int maxEpochs = 100000;
        size_t total_samples = 10;

        int max_val =  50;
        int min_val = -50;
    };

    GA(const GA_Params & p);

    void initialize();

    void process();

    void evaluation();
    void selection();
    void crossover();
    void crossPair(const size_t & i, const size_t & j, const size_t & startBit, const size_t & totalBits);
    void mutation();

    bool termination_condition(const int & epochs);

    GA_Params & params() { return m_params; }
    void setParams(const GA_Params & p) { m_params = p; }

    void generateLabeledData();

    int epochs() { return m_epochs; }

    void interrupt() { m_interrupt = true; }
    bool running() { return m_running; }

    const Particle & best() const { return m_best; }

    double uniformRandNormalized();

private:
    std::vector<Particle> m_population;
    Particle m_best;
    GA_Params m_params;
    int m_epochs = 0;
    bool m_interrupt = false;
    bool m_running = false;

    std::vector<double> m_inputs;
    std::vector<double> m_outputs;
};

#endif // GA_H
