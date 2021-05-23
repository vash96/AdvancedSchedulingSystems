#ifndef WL_BACKTRACKING_HH
#define WL_BACKTRACKING_HH
#include "BacktrackingOpt.hh"
#include "WL_Data.hh"

class BacktrackingWLOpt : public BacktrackingOpt<WL_Input, WL_Output, unsigned>
{
public:
	BacktrackingWLOpt(const WL_Input &in, unsigned fl) : BacktrackingOpt(in, fl) {}

protected:
	// hot-spots
	void FirstOfLevel();
	bool NextOfLevel();
	bool Feasible();
	unsigned Cost();
	// cold-spots
	bool NonImprovingBranch();
	void GoUpOneLevel();
};
#endif