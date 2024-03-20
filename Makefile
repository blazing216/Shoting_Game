all: main
	./main

main: main.cpp
	clang++ -o main -O2 main.cpp -std=c++17 -I/usr/loca/include -L/usr/local/lib -lsfml-window -lsfml-system -lsfml-graphics
