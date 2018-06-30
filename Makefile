# Makefile for Pixel Shootout
# If you're running Mac, you can build using Xcode
# If you're running Linux, this Makefile should help you
# On Windows, use the Visual Studio project
# You need to have a compiled version of Orx for your platform in the lib/ folder

ODIR=obj
OUTDIR=Build
OUTPUT=$(OUTDIR)/Pixel\ Shootout

CC=g++
FLAGS=-std=c++11 -c -o $(ODIR)/$(@F)
LD=-I inc/ -L lib/
LIB=-l orx
OBJS=Bullet.o Character.o Enemy.o Entity.o Environment.o Main.o Player.o StandAlone.o Weapon.o Item.o Obtainable.o Powerup.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

pixelshootout: copyassets $(_OBJS)
	$(CC) $(LD) $(_OBJS) $(LIB) -o $(OUTPUT)

copyassets:
	mkdir -p $(OUTDIR) $(ODIR)
	find data -name '*.png' -exec cp {} $(OUTDIR) \;
	cp -u bin/*.ini $(OUTDIR)

$(ODIR)/Bullet.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Combat/Bullet.cpp

$(ODIR)/Character.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Entities/Character.cpp

$(ODIR)/Enemy.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Entities/Enemy.cpp

$(ODIR)/Entity.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Entities/Entity.cpp

$(ODIR)/Environment.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/App/Environment.cpp

$(ODIR)/Main.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/App/Main.cpp

$(ODIR)/Player.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Entities/Player.cpp

$(ODIR)/StandAlone.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/App/StandAlone.cpp

$(ODIR)/Weapon.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Combat/Weapon.cpp

$(ODIR)/Item.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Items/Item.cpp

$(ODIR)/Obtainable.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Items/Obtainable.cpp

$(ODIR)/Powerup.o:
	$(CC) $(FLAGS) $(LD) Pixel\ Shootout/Items/Powerup.cpp

clean:
	rm -f $(OUTPUT) $(ODIR)/*.o

squeakyclean:
	rm -rf $(OUTPUT) $(ODIR)
