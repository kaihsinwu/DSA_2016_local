CC:= g++
CFLAGS:= -O3 -std=c++0x
input:=

all: invmat

invmat: invmat.o
	$(CC) $^ $(CFLAGS) -o $@

invmat.o: invmat.cpp
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: clean run rebuild

clean:
	@rm -rf *.o invmat

run:
	./invmat

rebuild: clean invmat
