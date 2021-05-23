#pragma once
#include "SingleSource.hpp"

namespace Assignment3
{
    class SingleSourceRandom : public Assignment2::SingleSource
    {
    private:
        static constexpr double EPS = 0.05;

    protected:
        WL_Pair Next();
    
    public:
        SingleSourceRandom(const WL_Input& in)
        : Assignment2::SingleSource(in) { }

    };
}