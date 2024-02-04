#include "PathDepOption02.h"
#include <cmath>

namespace fre {
    void Rescale(SamplePath& S, double x, int j)
    {
        int m = S.size();
        for (int k = 0; k < m; k++) S[k][j] = x * S[k][j];
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        int d = S[0].size();
        Vector one(d);
        for (int i = 0; i < d; i++) one[i] = 1.0;
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
        }
        if (Ave < K) return 0.0;
        return Ave - K;
    }
    
    double PathDepOption::PriceByMC(MCModel& Model, long N, double epsilon, 
                                    Vector& delta)
    {
        double H = 0.0;
        Vector S0 = Model.GetS0();
        int d = S0.size();
        Vector Heps(d);
        Vector one(d);
        for (int i = 0; i < d; i++) {
            Heps[i] = 0.0;
            one[i] = 1.0;
        }
        SamplePath S(m);

        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);
            for (int j = 0; j < d; j++){
                Rescale(S, 1.0 + epsilon, j);
                Heps[j] = (i * Heps[j] + Payoff(S)) / (i + 1.0);
                Rescale(S, 1/(1.0 + epsilon), j);
            }
        }
        Price = std::exp(-Model.GetR() * T) * H;
        delta = std::exp(-Model.GetR() * T) * (Heps - H*one) / (epsilon * S0);
        return Price;
    }
}
