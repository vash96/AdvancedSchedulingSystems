COMPILE_OPTIONS = -Wall -O3 -std=c++17 #-D BRANCH_BOUND

TestWLOpt.exe: TestWLOpt.o BacktrackingWLOpt.o WL_Data.o
	g++ -o TestWLOpt.exe TestWLOpt.o BacktrackingWLOpt.o WL_Data.o

TestWLOpt.o: BacktrackingWLOpt.hh BacktrackingOpt.hh TestWLOpt.cc WL_Data.hh
	g++ -c $(COMPILE_OPTIONS) TestWLOpt.cc

BacktrackingWLOpt.o: BacktrackingWLOpt.hh BacktrackingWLOpt.cc WL_Data.hh
	g++ -c $(COMPILE_OPTIONS) BacktrackingWLOpt.cc

WL_Data.o: WL_Data.cc WL_Data.hh
	g++ -c $(COMPILE_OPTIONS) WL_Data.cc

clean:
	rm -f TestWLOpt.exe TestWLOpt.o BacktrackingWLOpt.o WL_Data.o
