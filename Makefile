csvConvert: main.o
	g++ -o csvConvert main.o
main.o: main.cpp
	g++ -std=c++0x -c -g main.cpp
clean:
	rm -f *.0 *.gch