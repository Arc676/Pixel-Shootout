# Makefile for Pixel Shootout
# If you're running Mac, you can build using Xcode
# If you're running Linux, this Makefile should help you
# You need to have a compiled version of Orx for your platform in the lib/ folder
CC=g++
FLAGS=-std=c++11 -c
LD=-I inc/ -L lib/
LIB=-l orx
OBJS=Bullet.o Character.o Enemy.o Entity.o Environment.o Main.o Player.o StandAlone.o

pixelshootout: $(OBJS)
	$(CC) $(LD) $(OBJS) $(LIB) -o bin/pixelshootout

Bullet.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Bullet.cpp

Character.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Character.cpp

Enemy.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Enemy.cpp

Entity.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Entity.cpp

Environment.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Environment.cpp

Main.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Main.cpp

Player.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Player.cpp

StandAlone.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/StandAlone.cpp

clean:
	rm bin/pixelshootout *.o
