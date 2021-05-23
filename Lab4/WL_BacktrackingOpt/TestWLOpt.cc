#include "BacktrackingWLOpt.hh"
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
  BacktrackingWLOpt solver(in,in.Stores()-1);

  if (solver.Search())
  {
	 WL_Output out = solver.BestSolution();
	 cout << "Best solution found " << out 
		  <<   " (" << solver.NumNodes() << " nodes visited)" << endl;
  }
  else
    cout << "No solution exists" << endl;
  return 0;
}
  
