CC = g++
CFLAGS = -Wall
PROG1 = textures
PROG2 = ex1
PROG3 = ex2
PROG4 = ex3
PROG5 = ex4

SRCS1 = main.cpp
SRCS2 = ex1.cpp
SRCS3 = ex2.cpp
SRCS4 = ex3.cpp
SRCS5 = ex4.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lGLEW -lglfw -lGL -std=c++0x -lSOIL
endif

all: $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)

$(PROG1):	$(SRCS1)
	$(CC) $(CFLAGS) -o $(PROG1) $(SRCS1) $(LIBS)

$(PROG2):	$(SRCS2)
	$(CC) $(CFLAGS) -o $(PROG2) $(SRCS2) $(LIBS)

$(PROG3):	$(SRCS3)
	$(CC) $(CFLAGS) -o $(PROG3) $(SRCS3) $(LIBS)

$(PROG4):	$(SRCS4)
	$(CC) $(CFLAGS) -o $(PROG4) $(SRCS4) $(LIBS)

$(PROG5):	$(SRCS5)
	$(CC) $(CFLAGS) -o $(PROG5) $(SRCS5) $(LIBS)

clean:
	rm -f $(PROG)
