#include "MultiSource.hpp"

namespace Assignment2
{
    double MultiSource::CostFunction(const unsigned s, const unsigned w) const
    {
        double covered = static_cast<double>( min(out.ResidualAmount(s), out.ResidualCapacity(w)) );
        double costToCover = static_cast<double>( out.Load(w)>0 ? 0 : in.FixedCost(w)/4 );
        costToCover += in.SupplyCost(s, w) * covered;
        
        return warehouseMalus[w] + costToCover/covered;
    }

    void MultiSource::Initializer()
    {
        PData pdata;
        for(unsigned s=0; s<in.Stores(); ++s) {
            for(unsigned w=0; w<in.Warehouses(); ++w) {
                pdata.emplace_back(s, w, CostFunction(s, w));
            }
        }

        activePairs = PriorityQueue(pdata, in.Stores(), in.Warehouses());
    }

    WL_Pair MultiSource::Next()
    {
        WL_Pair best;
        do{
            best = activePairs.Top();
            activePairs.Pop();
        }while(not IsFeasible(best));

        return best;
    }

    bool MultiSource::IsFeasible(const WL_Pair& best) const
    {
        return out.ResidualAmount(best.s) > 0 and
                out.ResidualCapacity(best.w) > 0;
    }

    unsigned MultiSource::Supply(const WL_Pair& best)
    {
        unsigned covered = min( out.ResidualAmount(best.s), out.ResidualCapacity(best.w) );
        out.Assign(best.s, best.w, covered);

        return covered;
    }

    void MultiSource::Update(const WL_Pair& best)
    {
        auto ActiveS = [this](const unsigned s) {
            return out.ResidualAmount(s) > 0;
        };
        auto ActiveW = [this](const unsigned w) {
            return out.ResidualCapacity(w);
        };

        if(ActiveS(best.s)) {
            // Correct all pairs (best.s, w)
            for(unsigned w=0; w<in.Warehouses(); ++w) {
                if(ActiveW(w)) {
                    activePairs.Change(best.s, w, CostFunction(best.s, w));
                }
            }
        }

        if(ActiveW(best.w)) {
            // Correct all pairs (s, best.w)
            for(unsigned s=0; s<in.Stores(); ++s) {
                if(ActiveS(s)) {
                    activePairs.Change(s, best.w, CostFunction(s, best.w));
                }
            }
        }
    }
}