CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD
EXEC=Backend
OBJECTS=main.o csv.o student.o course.o hash.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d
