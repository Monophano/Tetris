all: main.o
	g++ main.o -o ./bin/app -L./lib -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	g++ -c ./src/main.cpp -I./include

clean:
	rm ./main.o