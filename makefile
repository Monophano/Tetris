tetris: main.o timer.o game.o grid.o block.o
	g++ -o ./build/tetris main.o timer.o game.o grid.o block.o -I./include -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	g++ -c ./src/main.cpp

timer.o:
	g++ -c ./src/timer.cpp

game.o:
	g++ -c ./src/game.cpp

grid.o:
	g++ -c ./src/grid.cpp

block.o:
	g++ -c ./src/block.cpp

clean:
	rm ./main.o
	rm ./game.o
	rm ./grid.o
	rm ./block.o
	rm ./timer.o

start:
	./build/tetris
