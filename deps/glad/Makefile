# 
# Author: David Kviloria
# Project: Andromeda-core
# 
CCX := g++ -std=c++11
COMPILER_FLAGS = -w

AR := ar rcs

build:
	$(CCX) $(COMPILER_FLAGS) -c ./include/glad.c && $(AR) ./libglad.a ./glad.o

clean:
	rm -rf libglad.a glad.o
