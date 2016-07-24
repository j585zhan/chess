CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -Wno-sign-compare -MMD -Werror=vla -I .
EXEC = chess
OBJECTS = main.o view.o textdisplay.o board.o chesspiece.o controller.o \
			piece/bishop.o piece/king.o piece/knight.o piece/pawn.o \
			piece/queen.o piece/rook.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
	