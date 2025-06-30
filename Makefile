build:
	g++ -std=c++11 -o main main.cpp
	./main
debug:
	g++ -std=c++11 -Wall -g main.cpp -o game_debug
clean:
	rm -rf ./main