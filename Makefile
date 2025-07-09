build:
	g++ -std=c++11 -o main main.cpp Collider.cpp
	./main
debug:
	g++ -std=c++11 -Wall -g main.cpp Collider.cpp -o game_debug
clean:
	rm -rf ./main