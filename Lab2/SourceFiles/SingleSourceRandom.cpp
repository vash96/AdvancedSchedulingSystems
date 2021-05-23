#include "SingleSourceRandom.hpp"
#include "Random.hh"


namespace Assignment3
{
    WL_Pair SingleSourceRandom::Next()
    {
        auto best = activePairs.back();
        
        // Delete junk
        while(not IsFeasible(best)) {
            activePairs.pop_back();
            best = activePairs.back();
        }

        // Random tie-brake
        unsigned n = 1;
        int i = activePairs.size()-1;
        int i_best = i;

        while(i>=0 and IsFeasible(activePairs[i]) and (activePairs[i].cost-best.cost)/best.cost <= EPS) {
            if(Random(1, n) == 1) {
                ++n;
                i_best = i;
            }
            --i;
        }

        // Get random-selected pair and erase it from datastructure
        swap(activePairs[i_best], activePairs.back());
        best = activePairs.back();
        activePairs.pop_back();

        return best;
    }
}