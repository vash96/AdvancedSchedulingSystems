#pragma once

struct WL_Pair {
    unsigned s, w;
    double cost;

    WL_Pair() { }
    WL_Pair(unsigned s, unsigned w, double c)
    : s(s), w(w), cost(c) { }

    bool operator<(const WL_Pair& rhs) const {
        return cost < rhs.cost;
    }
};