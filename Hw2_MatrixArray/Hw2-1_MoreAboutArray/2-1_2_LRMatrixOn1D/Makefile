CC := g++
CCFLAGS := -O3 -std=c++0x



all: lron1d



lron1d: lron1d.o
	$(CC) $(CCFLAGS) $^ -o $@

lron1d.o: lron1d.cpp
	$(CC) -c $(CCFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm *o lron1d


