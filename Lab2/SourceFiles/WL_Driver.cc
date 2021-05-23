#include <iostream>
#include <cstdlib>
#include "WL_Data.hh"
#include "WL_Greedy.hh"

int main(int argc, char* argv[])
{
  string instance;
  if (argc == 1)
    {
      cout << "Name of the file containing the instance:";
      cin >> instance;
    }
  else if (argc == 2)
    instance = argv[1];
  else
    {
      cerr << "Usage: " << argv[0] << " [input_file]" << endl;
      exit(1);
    }

  WL_Input in(instance);
  WL_Output out(in);
  GreedyWLSolver(in, out);
  cout << out << endl;
  cout << "Number of violations: " << out.ComputeViolations() << endl;
  cout << "Cost: " << out.ComputeCost() << endl;
  return 0;
}

