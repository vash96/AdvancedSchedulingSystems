#pragma once
#include "WL_Data.hh"
#include "WL_Pair.hpp"
#include <vector>
using namespace std;

template<typename Info,
         typename DataStructure>
class Assignment
{
protected:
    unsigned totalGoods;
    const WL_Input& in;
    WL_Output out;
    vector<double> warehouseMalus;
    DataStructure activePairs;

    void ComputeWMalus();

    virtual double CostFunction(const unsigned, const unsigned) const = 0;  // Rank function to initialize/maintain best info
    virtual void Initializer() = 0;                                         // Initialize database
    virtual Info Next() = 0;                                                // Consume next feasible Info strategy
    virtual bool IsFeasible(const Info&) const = 0;                         // Check feasibility
    virtual unsigned Supply(const Info&) = 0;                               // Supply strategy
    virtual void Update(const WL_Pair&) = 0;                                // Update database strategy

public:
    Assignment(const WL_Input&);
    unsigned Solve();
    WL_Output GetOutput() { return out; }
};

#include <iostream>

template<typename Info,
         typename DataStructure>
Assignment<Info, DataStructure>::Assignment(const WL_Input& in)
: totalGoods(0), in(in), out(in)
{
    for(unsigned s=0; s<in.Stores(); ++s) {
        totalGoods += in.AmountOfGoods(s);
    }

    ComputeWMalus();
}


template<typename Info,
         typename DataStructure>
void Assignment<Info, DataStructure>::ComputeWMalus()
{
    for(unsigned w=0; w<in.Warehouses(); ++w) {
        double malus = static_cast<double>(in.FixedCost(w)) / static_cast<double>(in.Capacity(w));
        warehouseMalus.emplace_back(malus);
    }
}

template<typename Info,
         typename DataStructure>
unsigned Assignment<Info, DataStructure>::Solve()
{
    Initializer();
    
    unsigned coveredGoods = 0;
    do {
        Info best = Next();
        coveredGoods += Supply(best);
        Update(best);

    }while(coveredGoods < totalGoods);

    cerr << "Final cost = " << out.ComputeCost() << "\n";
    cerr << "Final violations = " << out.ComputeViolations() << "\n\n";

    return out.ComputeCost();
}