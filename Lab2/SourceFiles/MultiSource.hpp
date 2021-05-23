#pragma once
#include "Assignment.hpp"
#include "PriorityQueue.hpp"
using namespace std;

namespace Assignment2
{
    class MultiSource : public Assignment<WL_Pair, PriorityQueue>
    {
    protected:
        double CostFunction(const unsigned, const unsigned) const override;
        void Initializer() override;
        WL_Pair Next() override;
        bool IsFeasible(const WL_Pair&) const override;
        unsigned Supply(const WL_Pair&) override;
        void Update(const WL_Pair&) override;

    public:
        MultiSource(const WL_Input& in)
        : Assignment(in) { }

    };
}