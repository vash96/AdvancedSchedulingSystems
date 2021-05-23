#pragma once
#include "Assignment.hpp"

namespace Assignment2
{
    class SingleSource : public Assignment<WL_Pair, vector<WL_Pair>>
    {
    protected:
        double CostFunction(const unsigned, const unsigned) const override;
        void Initializer() override;
        virtual WL_Pair Next() override;
        bool IsFeasible(const WL_Pair&) const override;
        unsigned Supply(const WL_Pair&) override;
        void Update(const WL_Pair&) override;


    public:
        SingleSource(const WL_Input& in)
        : Assignment(in) { }

    };
}