# Makefile for Pixel Shootout
# If you're running Mac, you can build using Xcode
# If you're running Linux, this Makefile should help you
# You need to have a compiled version of Orx for your platform in the lib/ folder
CC=g++
FLAGS=-std=c++11 -c
LD=-I inc/ -L lib/
LIB=-l orx
OBJS=Bullet.o Character.o Enemy.o Entity.o Environment.o Main.o Player.o StandAlone.o Weapon.o Item.o Obtainable.o Powerup.o

pixelshootout: $(OBJS)
	$(CC) $(LD) $(OBJS) $(LIB) -o linux/Pixel\ Shootout
	find data -name '*.png' -exec cp {} linux \;
	cp -u bin/*.ini linux

Bullet.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Combat/Bullet.cpp

Character.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Entities/Character.cpp

Enemy.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Entities/Enemy.cpp

Entity.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Entities/Entity.cpp

Environment.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/App/Environment.cpp

Main.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/App/Main.cpp

Player.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Entities/Player.cpp

StandAlone.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/App/StandAlone.cpp

Weapon.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Combat/Weapon.cpp

Item.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Items/Item.cpp

Obtainable.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Items/Obtainable.cpp

Powerup.o:
	$(CC) $(FLAGS) $(LD) Orx\ Vice/Items/Powerup.cpp

clean:
	rm linux/Pixel\ Shootout *.o
