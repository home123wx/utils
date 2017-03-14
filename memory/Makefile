OBJ = main.cpp WeakPointer.hpp
GCC = g++
Flags= -std=c++11
all:main

main:${OBJ}
	${GCC} ${OBJ} ${Flags} -o $@
#main.o:main.cpp
#	${GCC} -c $< -o $@
#WeakPointer.o:WeakPointer.hpp
#	${GCC} -c $< -o $@

clean:
	rm -rf *.o
	rm -rf main
