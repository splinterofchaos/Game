
CXX = g++
OPS = -Wall
O = 
OUT = run
LIBS = -lGL -lSDL

${OUT} : makefile main.cpp glpp.o Terrain.o Collision.o Controller.h draw_shape.o Tank.o
	${CXX} -o ${OUT} ${OPS} ${LIBS} main.cpp glpp.o draw_shape.o Terrain.o Collision.o Tank.o

Tank.o : Tank.h Tank.cpp Actor.h Rectangle.h Collision.o
	${CXX} -c Tank.cpp

Terrain.o : Terrain.h Terrain.cpp Actor.h Rectangle.h Collision.o
	${CXX} -c Terrain.cpp

Collision.o : Collision.h Collision.cpp
	${CXX} -c Collision.cpp

draw_shape.o : draw_shape.h draw_shape.cpp glpp.o
	${CXX} -c draw_shape.cpp

glpp.o : glpp.cpp glpp.h
	${CXX} -c glpp.cpp

clean : 
	rm *.o
