CXX = g++                                     # compiler
CXXFLAGS = -g -MMD                      # compiler flags
MAKEFILE NAME = ${firstword ${MAKEFILE LIST}} # makefile name

OBJECTS1 = helicopter.o eventHandler.o painter.o displayable.o xinfo.o column.o game.o
EXEC1 = run                                            # executable name

OBJECTS = ${OBJECTS1}
EXECS = ${EXEC1}
DEPENDS = ${OBJECTS:.o=.d}                    # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@ -L/usr/X11/X11R6 -lX11          

${OBJECTS} : ${MAKEFILE NAME}                 # OPTIO # => recompile

-include ${DEPENDS}                           # include *.d files con

clean :                                       # remove files that can 
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}
