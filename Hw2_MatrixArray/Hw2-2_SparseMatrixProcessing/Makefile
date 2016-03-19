CC := g++
CCFLAGS := -O3 -Wall -std=c++0x



all: smproc

smproc: smproc.o xstruct.o
	$(CC) $(CCFLAGS) $^ -o $@

smproc.o: smproc.cpp xstruct.hpp
	$(CC) -c $(CCFLAGS) $< -o $@

xstruct.o: xstruct.cpp xstruct.hpp
	$(CC) -c $(CCFLAGS) $< -o $@

.phony: clean


clean:
	rm *.o smproc
