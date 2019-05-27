CXX=c++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

main: functions.o student.o
	g++ -std=c++11 -o main main.cpp functions.o student.o
functions:
	g++ -std=c++11 -c functions.cpp
student:
	g++ -std=c++11 -c student.cpp
clean:
	rm *.o main
