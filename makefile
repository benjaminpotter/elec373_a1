
a1: main.o
	g++ -g -o bin/a1 build/main.o

main.o: src/main.cpp
	g++ -g -c -o build/main.o src/main.cpp

clean:
	rm build/*