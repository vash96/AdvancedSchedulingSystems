COMPILE_OPTIONS = -Wall -O3 -std=c++17 #-D ASSIGN3

TestWLEnumeration.exe: TestWLEnumeration.o WL_Enumeration.o WL_Data.o
	g++ -o TestWLEnumeration.exe TestWLEnumeration.o WL_Enumeration.o WL_Data.o

TestWLEnumeration.o: WL_Enumeration.hh EnumerationOpt.hh TestWLEnumeration.cc
	g++ -c $(COMPILE_OPTIONS) TestWLEnumeration.cc

WL_Enumeration.o: WL_Enumeration.hh WL_Enumeration.cc
	g++ -c $(COMPILE_OPTIONS) WL_Enumeration.cc

WL_Data.o: WL_Data.cc WL_Data.hh
	g++ -c $(COMPILE_OPTIONS) -c WL_Data.cc

clean:
	rm -f *.o *.exe