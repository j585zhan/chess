CXX = g++-5
EXTRA = -DTEXT
CXXFLAGS = -g -std=c++14 -Wall -Wno-sign-compare -MMD -Werror=vla -I .
CXXFLAGS += ${EXTRA}
EXEC = chess
OBJECTS = main.o view.o unicodedisplay.o textdisplay.o board.o chesspiece.o controller.o \
			piece/bishop.o piece/king.o piece/knight.o piece/pawn.o \
			piece/queen.o piece/rook.o graphicdisplay.o xwindow/window.o ai.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${EXTRA} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean text unicode graphic_unicode

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

graphic: 
	make EXTRA="-DGRAPHIC -DTEXT"

unicode:
	make EXTRA="-DUNICODE"

graphic_unicode:
	make EXTRA="-DGRAPHIC -DUNICODE"
