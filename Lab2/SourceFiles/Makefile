OPTIONS = -Wall -O3 -std=c++17

WL_Test.exe: WL_Driver.o WL_Data.o WL_Greedy.o Random.o PriorityQueue.o \
				SingleSource.o SingleSourceRandom.o MultiSource.o
	g++ *.o -o WL_Test.exe

WL_Data.o: WL_Data.cc WL_Data.hh
	g++ $(OPTIONS) -c WL_Data.cc

WL_Greedy.o: WL_Greedy.cc WL_Greedy.hh WL_Data.hh SingleSource.hpp MultiSource.hpp \
				SingleSourceRandom.hpp WL_Pair.hpp PriorityQueue.hpp Assignment.hpp
	g++ $(OPTIONS) -c WL_Greedy.cc

WL_Driver.o: WL_Driver.cc WL_Greedy.hh WL_Data.hh
	g++ $(OPTIONS) -c WL_Driver.cc

Random.o: Random.cc Random.hh
	g++ $(OPTIONS) -c Random.cc 

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.hpp WL_Pair.hpp
	g++ $(OPTIONS) -c PriorityQueue.cpp

SingleSource.o: SingleSource.cpp SingleSource.hpp WL_Pair.hpp Assignment.hpp WL_Data.hh
	g++ $(OPTIONS) -c SingleSource.cpp

SingleSourceRandom.o: SingleSourceRandom.cpp SingleSourceRandom.hpp SingleSource.hpp \
						WL_Pair.hpp Assignment.hpp WL_Data.hh Random.hh
	g++ $(OPTIONS) -c SingleSourceRandom.cpp

MultiSource.o: MultiSource.cpp MultiSource.hpp WL_Pair.hpp Assignment.hpp WL_Data.hh \
				PriorityQueue.hpp
	g++ $(OPTIONS) -c MultiSource.cpp

clean:
	rm -f *.o WL_Test.exe
