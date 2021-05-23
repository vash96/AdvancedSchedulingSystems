#include "WL_Enumeration.hh"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
  string file_name;

  if (argc == 2)
    file_name = argv[1];
  else if (argc == 1)
    {
      cout << "Input file name: ";
      cin >> file_name;
    }

  WL_Input in(file_name);
  EnumerationWLOpt solver(in);
  
  if (solver.Search())
    cout << "Best solution found " << solver.BestSolution()
         << " after  " << solver.NumSol() 
         << " iterations" << endl;
  else
    cout << "No solution exists" << endl;
  return 0;
}
