// File WL_Data.cc
#include "WL_Data.hh"
#include <fstream>

WL_Input::WL_Input(string file_name)
{  
  const unsigned MAX_DIM = 100;
  unsigned w, s;
  char ch, buffer[MAX_DIM];

  ifstream is(file_name);
  if(!is)
  {
    cerr << "Cannot open input file " <<  file_name << endl;
    exit(1);
  }
  
  is >> buffer >> ch >> warehouses >> ch;
  is >> buffer >> ch >> stores >> ch;
  
  capacity.resize(warehouses);
  fixed_cost.resize(warehouses);
  amount_of_goods.resize(stores);
  supply_cost.resize(stores,vector<unsigned>(warehouses));
  
  // read capacity
  is.ignore(MAX_DIM,'['); // read "... Capacity = ["
  for (w = 0; w < warehouses; w++)
    is >> capacity[w] >> ch;
  
  // read fixed costs  
  is.ignore(MAX_DIM,'['); // read "... FixedCosts = ["
  for (w = 0; w < warehouses; w++)
    is >> fixed_cost[w] >> ch;

  // read goods
  is.ignore(MAX_DIM,'['); // read "... Goods = ["
  for (s = 0; s < stores; s++)
    is >> amount_of_goods[s] >> ch;

  // read supply costs
  is.ignore(MAX_DIM,'['); // read "... SupplyCost = ["
  is >> ch; // read first '|'
  for (s = 0; s < stores; s++)
  {	 
    for (w = 0; w < warehouses; w++)
      is >> supply_cost[s][w] >> ch;
  }
  is >> ch >> ch;
}

ostream& operator<<(ostream& os, const WL_Input& in)
{
  unsigned w, s;
  os << "Warehouses = " << in.warehouses << ";" << endl;
  os << "Stores = " << in.stores << ";" << endl;
  os << endl;
  
  os << "Capacity = [";
  for (w = 0; w < in.warehouses; w++)
    {
      os << in.capacity[w];
      if (w < in.warehouses - 1)
        os << ", ";
      else
        os << "];" << endl;
    }
  
  os << "FixedCost = [";
  for (w = 0; w < in.warehouses; w++)
    {
      os << in.fixed_cost[w];
      if (w < in.warehouses - 1)
        os << ", ";
      else
        os << "];" << endl;
    }
  
  os << "Goods = [";
  for (s = 0; s < in.stores; s++)
    {
      os << in.amount_of_goods[s];
      if (s < in.stores - 1)
        os << ", ";
      else
        os << "];" << endl;
    }
  
  os << "SupplyCost = [|";
  for (s = 0; s < in.stores; s++)
    {
      for (w = 0; w < in.warehouses; w++)
	  {
         os << in.supply_cost[s][w];
         if (w < in.warehouses - 1)
           os << ",";
         else
           os << "|" << endl;
	  }
    }
  os << "];" << endl;
  
  return os;
}

WL_Output::WL_Output(const WL_Input& my_in)
  : 
#ifdef ASSIGN3
    over(0), cost(0), isOver(my_in.Warehouses(), false), clients(my_in.Warehouses(), 0),
#endif
    in(my_in), assignment(in.Stores(),-1), 
    load(in.Warehouses(),0)
{}

WL_Output& WL_Output::operator=(const WL_Output& out)
{
#ifdef ASSIGN3
  over = out.over;
  cost = out.cost;
  isOver = out.isOver;
  clients = out.clients;

#endif

  assignment = out.assignment;
  load = out.load;
  return *this;
}

void WL_Output::Assign(unsigned s, unsigned w)
{
  int w_old = assignment[s];
  
  if (w_old != -1) {
    load[w_old] -= in.AmountOfGoods(s);

#ifdef ASSIGN3
    if(isOver[w_old] and load[w_old] <= in.Capacity(w_old)) {
      isOver[w_old] = false;
      --over;
    }
    cost -= in.AmountOfGoods(s) * in.SupplyCost(s, w_old);
    --clients[w_old];
    if(clients[w_old] == 0) {
      cost -= in.FixedCost(w_old);
    }

#endif
  }

  assignment[s] = w;
  load[w] += in.AmountOfGoods(s);

#ifdef ASSIGN3
  if(not isOver[w] and load[w] > in.Capacity(w)) {
    isOver[w] = true;
    ++over;
  }
  cost += in.AmountOfGoods(s) * in.SupplyCost(s, w);
  ++clients[w];
  if(clients[w] == 1) {
    cost += in.FixedCost(w);
  }

#endif
}

unsigned WL_Output::ComputeCost() const
{
#ifndef ASSIGN3
  unsigned s, w, cost = 0;
  for (s = 0; s < in.Stores(); s++)
    {
      w = assignment[s];
      cost += in.AmountOfGoods(s) * in.SupplyCost(s,w);
    }
  for (w = 0; w < in.Warehouses(); w++)
    if (load[w] > 0)
      cost += in.FixedCost(w);

#endif

  return cost;
}

unsigned WL_Output::ComputeViolations() const
{
#ifndef ASSIGN3
  unsigned w, violations = 0;
  for (w = 0; w < in.Warehouses(); w++)
    if (load[w] > in.Capacity(w))
      violations++;
  return violations;

#else
  return over;

#endif
}

ostream& operator<<(ostream& os, const WL_Output& out)
{ 
  unsigned s, w;
  os << "[";
  for (s = 0; s < out.in.Stores(); s++)
    {
      os << out.assignment[s];
      if (s < out.in.Stores() - 1)
        os << ", ";
    }
  os << "],";

  os << " (";
  for (w = 0; w < out.in.Warehouses(); w++)
    { 
      os << out.load[w];
      if (w < out.in.Warehouses() - 1)
        os << ", ";
    }
  os << ")";
  return os;
}

// istream& operator>>(istream& is, WL_Output& out)
// {
//   unsigned s, w, q;
//   out.Reset();
//   char ch;
//   is >> ch;
//   for (s = 0; s < out.in.Stores(); s++)
//     {
//       is >> ch;
//       for (w = 0; w < out.in.Warehouses(); w++)
//         {
//           is >> q >> ch;
//           out.Assign(s,w,q);
//         }
//       is >> ch;
//     }
//   return is;
// }
