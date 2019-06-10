PROG=teddi
CFLAGS=-lSDL -lGL -lSDL_mixer -lSDL_ttf -W -Wall -g -Debug
LDFLAGS=-s
CXX=g++
GET=co
SRCS=GraphicCore.cpp EventCore.cpp Keyboard.cpp SoundCore.cpp Sound.cpp FontCore.cpp LogicCore.cpp\
	Texture.cpp Sprite.cpp Map.cpp Creature.cpp Placeable.cpp Dummy.cpp Weapon.cpp Bullet.cpp Player.cpp Animation.cpp\
	math.cpp Sync.cpp Object.cpp Scorebar.cpp main.cpp 
OBJS=GraphicCore.o EventCore.o Keyboard.o SoundCore.o Sound.o FontCore.o Weapon.o Bullet.o LogicCore.o\
	Texture.o Sprite.o Creature.o Map.o Placeable.o Dummy.o Player.o Animation.o Scorebar.o\
	math.o Sync.o Object.o main.o 

SRCS=$(shell find src/ -type f -name "*.cpp")
OBJS=$(SRCS:.cpp=.o)

DEPEND= makedepend $(CFLAGS)

all:	$(PROG)

# To make an executable
$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(LDFLAGS) $(CFLAGS)

# To install things in the right place
#install: $(PROG)
#        $(INSTALL) -c -o $(OWNER) -g $(GROUP) -m 755 $(PROG) $(BINDIR)
#        $(INSTALL) -c -o $(OWNER) -g $(GROUP) -m 644 printenv.man $(MANDIR)

# what have I done wrong?
lint: $(SRCS)
	lint $(CFLAGS) $(SRCS)

# what are the source dependencies
depend: $(SRCS)
	$(DEPEND) $(SRCS)

# clean out the dross
clean:
	-rm $(PROG) src/*.o

