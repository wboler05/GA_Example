#include "particle.h"

Particle::Particle()
{

}

Particle::~Particle() {

}

Particle::Particle(const Particle & l) :
    m_state(l.m_state),
    m_cost(l.m_cost)
{

}

Particle::Particle(Particle && r) :
    m_state(std::move(r.m_state)),
    m_cost(std::move(r.m_cost))
{

}

Particle & Particle::operator= (const Particle & l) {
    m_state = l.m_state;
    m_cost = l.m_cost;
    return *this;
}

Particle & Particle::operator= (Particle && r) {
    m_state = std::move(r.m_state);
    m_cost = std::move(r.m_cost);
    return *this;
}
