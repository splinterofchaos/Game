
CXX = g++
OPS = -Wall
O = 
OUT = run
LIBS = -lGL -lSDL

${OUT} : makefile main.cpp Tank.h Terrain.h Collision.h Controller.h
	${CXX} -o ${OUT} ${OPS} ${LIBS} main.cpp
