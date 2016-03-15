CC := g++
CCFLAGS := -O3 -std=c++0x



all: transpose


transpose: transpose.o
	$(CC) $(CCFLAGS) $^ -o $@

transpose.o: transpose.cpp
	$(CC) -c $(CCFLAGS) $^ -o $@

.PHONY: clean run

clean:
	rm *o transpose

run :
	./transpose 10

