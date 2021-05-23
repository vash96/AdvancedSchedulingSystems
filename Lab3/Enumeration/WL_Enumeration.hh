#include "EnumerationOpt.hh"
#include "WL_Data.hh"

// insert here the definition of the class EnumerationWLOpt
class EnumerationWLOpt : public EnumerationOpt<WL_Input, WL_Output, unsigned>
{
public:
    void First() override;
    bool Next() override;
    bool Feasible() override;
    unsigned Cost() override;

    EnumerationWLOpt(const WL_Input& in)
    : EnumerationOpt(in) { }
};