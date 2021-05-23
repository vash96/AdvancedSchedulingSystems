#define NDEBUG

#include "SingleSource.hpp"
#include "MultiSource.hpp"
#include "SingleSourceRandom.hpp"
#include "WL_Greedy.hh"
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
using namespace std;

void GreedyWLSolver(const WL_Input& in, WL_Output& out)
{
    // Assignment 1:
    // select stores in input order and assign them completely to the first (in input order) feasible warehouse

    auto IsFeasible = [&](const unsigned s, const unsigned w) {
        return in.AmountOfGoods(s) <= out.ResidualCapacity(w);
    };

    for(unsigned s=0; s<in.Stores(); ++s) {
        // Find first feasible   
        unsigned w = 0;
        while(w<in.Warehouses() and not IsFeasible(s, w)) {
            ++w;
        }

        // If none is feasible, assign to warehouse 0
        if(w == in.Warehouses()) {
            w = 0;
        }

        // Assign
        out.FullAssign(s, w);
    }

    cerr << "Final cost = " << out.ComputeCost() << "\n";
    cerr << "Final violations = " << out.ComputeViolations() << "\n\n";

    // auto t0 = clock();
    // Assignment2::SingleSource ss(in);
    // cerr << "Solving Single Source...\n";
    // ss.Solve();
    // cerr << "Time... " << static_cast<double>(clock()-t0)/CLOCKS_PER_SEC << "s\n\n";

    // t0 = clock();
    // cerr << "Solving Single Source with random tie-break...\n";
    // unsigned best = 1e9;
    // for(int i=0; i<10; ++i) {
    //     Assignment3::SingleSourceRandom ssr(in);
    //     best = min(best, ssr.Solve());
    // }
    // cerr << "Best = " << best << "\n";
    // cerr << "Time... " << static_cast<double>(clock()-t0)/CLOCKS_PER_SEC << "s\n\n";

    // t0 = clock();
    // Assignment2::MultiSource ms(in);
    // cerr << "Solving Multi Source...\n";
    // ms.Solve();
    // cerr << "Time... " << static_cast<double>(clock()-t0)/CLOCKS_PER_SEC << "s\n\n";
}