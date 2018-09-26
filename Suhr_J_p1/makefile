P=program1
CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(P)

$(P).o: $(P).cpp
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(P): $(P).o
	g++ $(CFLAGS) $(P).o -o $(P)

run: all
	./$(P) -m market-price-test.txt -p price-list-test.txt

checkmem: all
	valgrind ./$(P)

clean:
	rm $(P).o
	rm $(P)
