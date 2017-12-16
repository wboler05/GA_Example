#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <limits>

class Particle
{
public:
    Particle();

    ~Particle();
    Particle(const Particle &);
    Particle(Particle &&);
    Particle & operator= (const Particle & );
    Particle & operator= (Particle &&);

    std::vector<double> & state() { return m_state; }

    const double & cost() const { return m_cost; }
    void setCost(const double & c) { m_cost = c; }

private:
    std::vector<double> m_state;
    double m_cost = std::numeric_limits<double>::max();
};

#endif // PARTICLE_H
