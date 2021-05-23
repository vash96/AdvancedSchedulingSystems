// File WL_Data.hh
#ifndef WL_DATA_HH
#define WL_DATA_HH
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


class WL_Input 
{
  friend ostream& operator<<(ostream& os, const WL_Input& in);
public:
  WL_Input(string file_name);
  unsigned Stores() const { return stores; }
  unsigned Warehouses() const { return warehouses; }
  unsigned Capacity(unsigned w) const { return capacity[w]; }
  unsigned FixedCost(unsigned w) const { return fixed_cost[w]; }
  unsigned AmountOfGoods(unsigned s) const { return amount_of_goods[s]; }
  unsigned SupplyCost(unsigned s, unsigned w) const { return supply_cost[s][w]; }
 private:
  unsigned stores, warehouses;
  vector<unsigned> capacity;
  vector<unsigned> fixed_cost;
  vector<unsigned> amount_of_goods;
  vector<vector<unsigned>> supply_cost;
};
class WL_Output 
{
  friend ostream& operator<<(ostream& os, const WL_Output& out);
  friend istream& operator>>(istream& is, WL_Output& out);
public:
  WL_Output(const WL_Input& i);
  WL_Output& operator=(const WL_Output& out);
  void Reset();
  unsigned Supply(unsigned s, unsigned w) const { return supply[s][w]; }
  unsigned Load(unsigned w) const { return load[w]; }
  unsigned ResidualCapacity(unsigned w) const { return in.Capacity(w) - load[w]; }
  unsigned AssignedGoods(unsigned s) const { return assigned_goods[s]; }
  unsigned ResidualAmount(unsigned s) const { return in.AmountOfGoods(s) - assigned_goods[s]; }
  void FullAssign(unsigned s, unsigned w); // assign completely s to w
  void Assign(unsigned s, unsigned w, unsigned q); // assign q goods of s to w
  unsigned ComputeCost() const;
  unsigned ComputeSupplyCost() const;
  unsigned ComputeLocationCost() const;
  unsigned ComputeViolations() const;
private:
  const WL_Input& in;
  vector<vector<unsigned>> supply;
  vector<unsigned> assigned_goods;   // quantity of goods of each store already assigned to warehouses
  vector<unsigned> load;   // quantity of goods of each warehouse assigned to stores
};
#endif
