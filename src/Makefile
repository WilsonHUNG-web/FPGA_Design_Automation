CC          := g++

CXXFLAGS        := -O3 -Wall -std=c++11

../bin/project: main.cpp io.h io.cpp timer.h irl.h irl.cpp sa.h sa.cpp
		$(CC) $(CXXFLAGS) -pthread -o $@ $? 
clean:
		rm -f ../bin/project

veryclean:
		rm -f ../bin/project
		rm -f ../output/*.floorplan