#include "ga.h"
#include <QApplication>

GA::GA(const GA_Params & p) :
    m_params(p)
{

}

void GA::initialize() {
    m_interrupt = false;

    m_population.resize(m_params.populationSize);
    for (size_t i = 0; i < m_population.size(); i++) {
        m_population[i].state().resize(Fitness::coeffs());
        for (size_t j = 0; j < Fitness::coeffs(); j++) {
            m_population[i].state()[j] = RandomNumber::uniformReal(m_params.min_val, m_params.max_val);
        }
    }
}

void GA::process() {

    m_running = true;

    m_epochs = 0;
    bool terminate = true;

    initialize();

    do {
        qApp->processEvents();

        evaluation();
        selection();
        crossover();
        mutation();
        terminate = termination_condition(++m_epochs);
    } while (!terminate);

    m_running = false;
}

void GA::evaluation() {
    generateLabeledData();

    double maxError = (std::numeric_limits<double>::max()-1.0) / static_cast<double>(m_inputs.size() * m_population.size());

    for (size_t i = 0; i < m_population.size(); i++) {
        Particle & p = m_population[i];

        double cost = 0;

        for (size_t sample = 0; sample < m_inputs.size(); sample++) {
            double prediction = Fitness::function(p.state(), m_inputs[sample]);
            cost += std::pow(prediction - m_outputs[sample], 2);

        }
        cost /= static_cast<double>(m_inputs.size());
        if (cost > maxError) {
            cost = maxError;
        }
        p.setCost(cost);
    }

    for (size_t i = 0; i < m_population.size(); i++) {
        if (m_best.cost() > m_population[i].cost()) {
            m_best = m_population[i];
        }
    }

}

void GA::selection() {
    std::vector<Particle> candidates;
    std::vector<double> cdf;
    candidates.resize(m_population.size());
    cdf.resize(m_population.size());

    // Get total cost for normalization
    double totalCost = 0;
    for (size_t i = 0; i < m_population.size(); i++) {
        totalCost += m_population[i].cost();
    }

    // Construct cdf
    for (size_t i = 0; i < m_population.size(); i++) {
        cdf[i] = 1.0 - (m_population[i].cost() / totalCost);
        cdf[i] /= static_cast<double>(m_population.size());
        if (i != 0) {
            cdf[i] += cdf[i-1];
        }
    }

    for (size_t i = 0; i < m_population.size(); i++) {
        double randVal = uniformRandNormalized();
        size_t sel = 0;
        for (;sel < m_population.size(); sel++) {
            if (cdf[sel] > randVal) {
                sel++;
                break;
            }
        }
        sel--;
        candidates[i] = m_population[sel];
    }

    m_population = candidates;
}

void GA::crossover() {
    int totalBits = 0;
    if (m_population.size() > 0) {
        totalBits = sizeof(m_population[0].state()[0]) * 8;
    } else {
        return;
    }

    for (size_t i = 0; i < m_population.size(); i++) {
        for (size_t j = i+1; j < m_population.size(); j++) {
            double randVal = uniformRandNormalized();
            if (uniformRandNormalized() > m_params.crossoverRate) {
                int startBit = RandomNumber::uniformInt(0, totalBits);
                crossPair(i, j, startBit, totalBits);

            }
        }
    }
}

void GA::crossPair(const size_t & i, const size_t & j, const size_t & startBit, const size_t & totalBits) {
    for (size_t k = 0; k < m_population[i].state().size(); k++) {
        for (size_t t = startBit; t < totalBits; t++) {
            uint64_t  mask = 1;
            for (size_t g = 0; g < t; g++ ) {
                mask = mask << 1 | 1;
            }
            uint64_t swapBit1 = (*(uint64_t * )(&m_population[i].state()[k])) & mask;
            uint64_t swapBit2 = (*(uint64_t * )(&m_population[j].state()[k])) & mask;
            uint64_t newVal1 = (*(uint64_t * )(&m_population[i].state()[k])) & ~mask;
            uint64_t newVal2 = (*(uint64_t * )(&m_population[j].state()[k])) & ~mask;
            newVal1 += swapBit1;
            newVal2 += swapBit2;
            m_population[i].state()[k] = *(double *)(&newVal1);
            m_population[j].state()[k] = *(double *)(&newVal2);

        }
    }
}

void GA::mutation() {

    for (size_t i = 0; i < m_population.size(); i++) {
        for (size_t j = 0; j < m_population[i].state().size(); j++) {
            int bits = sizeof(m_population[i].state()[j]) * 8;
            for (int k = 0; k < bits; k++) {
                double randVal = uniformRandNormalized();
                if (randVal < m_params.mutationRate) {
                    uint64_t newVal = (1 << k) ^ (*(uint64_t * )(&m_population[i].state()[j]));
                    m_population[i].state()[j] = *(double*)(&newVal);
                }
            }
        }
    }

}

bool GA::termination_condition(const int & epochs) {
    if (m_best.cost() < m_params.terminationCost || epochs > m_params.maxEpochs || m_interrupt) {
        return true;
    } else {
        return false;
    }
}

void GA::generateLabeledData() {
    m_inputs.resize(m_params.total_samples);
    m_outputs.resize(m_params.total_samples);
    for (size_t i = 0; i < m_params.total_samples; i++) {
        m_inputs[i] = RandomNumber::uniformReal(-50, 50);
        m_outputs[i] = Fitness::realFunctionToEmulate(m_inputs[i]);

//        qDebug() << "Inputs: " << m_inputs[i] << "\tOutputs: " << m_outputs[i];
    }
}

double GA::uniformRandNormalized() {
    return RandomNumber::uniformReal(0, 1);
}
