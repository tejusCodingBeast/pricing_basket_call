#pragma once

#include "MCModel02.h"

namespace fre {
    class PathDepOption
    {
    protected:
        double Price;
        double T;
        double K;
        int m;
    public:
        PathDepOption(double T_, double K_, int m_) : Price(0.0), T(T_), K(K_), m(m_) {}
        double PriceByMC(MCModel& Model, long N, double epsilon, Vector& delta);
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_) : PathDepOption(T_, K_, m_) {}
        double Payoff(const SamplePath& S) const;
    };
}

