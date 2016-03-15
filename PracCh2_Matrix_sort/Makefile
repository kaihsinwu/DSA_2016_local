CC := g++
CCFLAGS := -O3 -std=c++0x




all: SortMethod

SortMethod: SortMethod.o
	$(CC) $(CCFLAGS) $^ -o $@

SortMethod.o: SortMethod.cpp
	$(CC) -c $(CCFLAGS) $^ -o $@
.PHONY: clean

clean:
	rm *.o SortMethod


