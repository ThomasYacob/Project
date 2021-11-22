# A simple Makefile for compiling small SDL projects

theGame: main.o collision.o car.o menu.o menuSystem.o enemyCars.o
	gcc -o theGame main.o collision.o car.o menu.o menuSystem.o enemyCars.o -lSDL2 -lSDL2_image -lSDL2_net
main.o: main.c 
	gcc -Wall -c main.c
collision.o: collision.c
	gcc -Wall -c collision.c
car.o: car.c
	gcc -Wall -c car.c
menu.o: menu.c
	gcc -Wall -c menu.c
menuSystem.o: menuSystem.c
	gcc -Wall -c menuSystem.c
enemyCars.o: enemyCars.c
	gcc -Wall -c enemyCars.c