all: main.o grid.o
	g++ main.o grid.o -o ./bin/app -L./lib -lsfml-graphics -lsfml-window -lsfml-system
	./bin/app

main.o:
	g++ -c ./src/main.cpp -I./include

grid.o:
	g++ -c ./src/grid.cpp -I./include

start:
	./bin/app

clean:
	rm ./main.o