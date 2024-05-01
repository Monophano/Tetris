all: main.o grid.o tetromino.o run
	g++ main.o grid.o tetromino.o -o ./bin/app -L./lib -lsfml-graphics -lsfml-window -lsfml-system -Wall
	run

main.o:
	g++ -c ./src/main.cpp -I./include

grid.o:
	g++ -c ./src/grid.cpp -I./include

tetromino.o:
	g++ -c ./src/tetromino.cpp -I./include

run:
	./bin/app > run.log

log:
	more run.log

cls:
	rm ./main.o
	rm ./grid.o
	rm ./tetromino.o
