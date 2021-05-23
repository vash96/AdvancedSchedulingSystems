#include "WL_Enumeration.hh"

// Insert here the code in the method of class EnumerationWLOpt
void EnumerationWLOpt::First()
{
    for(unsigned s=0; s<in.Stores(); ++s) {
        out.Assign(s, 0);
    }
}


bool EnumerationWLOpt::Next()
{
    unsigned firstMax = 0;
    const unsigned W = in.Warehouses()-1;
    const unsigned S = in.Stores();

    while(firstMax < S and static_cast<unsigned>(out.Assignment(firstMax)) == W) {
        out.Assign(firstMax, 0);
        ++firstMax;
    }

    if(firstMax == S) { // No more solutions to enumerate
        return false;
    }

    out.Assign(firstMax, out.Assignment(firstMax)+1);

    return true;
}


bool EnumerationWLOpt::Feasible()
{
#ifndef ASSIGN3
    vector<unsigned> load(in.Warehouses(), 0);

    // Each warehouse has load <= Capacity
    for(unsigned s=0; s<in.Stores(); ++s) {
        unsigned w = out.Assignment(s);
        load[w] += in.AmountOfGoods(s);
        if(load[w] > in.Capacity(w)) {
            return false;
        }
    }

    return true;

#else
    return out.Feasible();

#endif
}

unsigned EnumerationWLOpt::Cost()
{
#ifndef ASSIGN3
    vector<bool> isOpen(in.Warehouses(), false);
    unsigned cost = 0;

    // Accumulate costs and which warehouses are open
    for(unsigned s=0; s<in.Stores(); ++s) {
        unsigned w = out.Assignment(s);
        cost += in.AmountOfGoods(s) * in.SupplyCost(s, w);
        if(not isOpen[w]) {
            isOpen[w] = true;
            cost += in.FixedCost(w);
        }
    }
    
    return cost;

#else
    return out.Cost();

#endif
}