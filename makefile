tetris: main.o timer.o game.o grid.o block.o
	g++ -o ./build/tetris main.o timer.o game.o grid.o block.o -I./include -L./lib -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	g++ -I./include/ -c ./src/main.cpp

timer.o:
	g++ -I./include/ -c ./src/timer.cpp

game.o:
	g++ -I./include -c ./src/game.cpp

grid.o:
	g++ -I./include -c ./src/grid.cpp

block.o:
	g++ -I./include -c ./src/block.cpp

clean:
	rm ./main.o
	rm ./game.o
	rm ./grid.o
	rm ./block.o
	rm ./timer.o

start:
	./build/tetris
