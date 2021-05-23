#include "SingleSource.hpp"
#include <algorithm>
using namespace std;

namespace Assignment2
{
    double SingleSource::CostFunction(const unsigned s, const unsigned w) const
    {
        double covered = static_cast<double>( in.AmountOfGoods(s) );
        double costToCover = static_cast<double>( out.Load(w) > 0 ? 0 : in.FixedCost(w)/4 );
        costToCover += in.SupplyCost(s, w) * in.AmountOfGoods(s);

        return warehouseMalus[w] + costToCover/covered;
    }

    void SingleSource::Initializer()
    {
        for(unsigned s=0; s<in.Stores(); ++s) {
            for(unsigned w=0; w<in.Warehouses(); ++w) {
                if(in.AmountOfGoods(s) <= in.Capacity(w)) {
                    activePairs.emplace_back(s, w, CostFunction(s, w));
                }
            }
        }
        sort(activePairs.rbegin(), activePairs.rend()); // Sort non-increasing with reverse_iterators
    }

    WL_Pair SingleSource::Next()
    {
        WL_Pair best{0, 0, -1};
        do {
            best = activePairs.back();
            activePairs.pop_back();
        }while(not IsFeasible(best));

        return best;
    }

    bool SingleSource::IsFeasible(const WL_Pair& best) const
    {
        return  out.ResidualAmount(best.s)>0 and
                in.AmountOfGoods(best.s) <= out.ResidualCapacity(best.w);
    }

    unsigned SingleSource::Supply(const WL_Pair& best)
    {
        out.FullAssign(best.s, best.w);
        return in.AmountOfGoods(best.s);
    }

    void SingleSource::Update(const WL_Pair& best)
    {
        // Nothing to update
    }
}
