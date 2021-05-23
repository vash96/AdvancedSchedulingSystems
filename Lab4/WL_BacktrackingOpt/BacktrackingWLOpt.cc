#include "BacktrackingWLOpt.hh"
#include <cassert>

void BacktrackingWLOpt::FirstOfLevel()
{
	out.Assign(level, 0);
}

bool BacktrackingWLOpt::NextOfLevel()
{
	unsigned w = out.Assignment(level);
	
	if(w+1 < in.Warehouses()) {
		out.Assign(level, w+1);
		return true;
	}else {
		return false;
	}
}

bool BacktrackingWLOpt::Feasible()
{
	if(level == -1) return true;
	unsigned w = out.Assignment(level);
	return out.Load(w) <= in.Capacity(w);
}

unsigned BacktrackingWLOpt::Cost()
{
	return out.TotalCost();
}

bool BacktrackingWLOpt::NonImprovingBranch()
{
	// Lower-bound of solution:
	// all remaining stores are assigned to least cost non full warehouse
	unsigned lb = 0;

#ifdef BRANCH_BOUND
	for(int s = level+1; s<=final_level; ++s) {
		unsigned lowcost = 1e9;
		for(unsigned w=0; w<in.Warehouses(); ++w) {
			if(out.Load(w)+in.AmountOfGoods(s) <= in.Capacity(w)) {
				lowcost = min(lowcost, in.SupplyCost(s, w) * in.AmountOfGoods(s));
			}
		}
		lb += lowcost;
	}
#endif

	return out.TotalCost()+lb >= best.TotalCost();
}

void BacktrackingWLOpt::GoUpOneLevel()
{
	// Unassign current-level store and go up
	out.Assign(level, -1);
	--level;
}
