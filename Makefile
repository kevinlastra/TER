CXX=g++
CXX_FLAGS=-Wall -ansi -pedantic -g -std=c++17
DEPEND=.depend

PROG=main
SOURCES=main.cpp Lecture.cpp Piece.cpp Coord.cpp TimeLine.cpp Identify.cpp Comparer.cpp ChessPlate.cpp TimeDivision.cpp Erreur_manager.cpp ArbreMovement.cpp

ifeq ($(wildcard $(DEPEND)),)
all: $(PROG)
else
all: $(PROG)
include $(DEPEND)
endif

$(PROG): $(SOURCES:.cpp=.o)
	$(CXX) $^ -o $@; make clean
$(DEPEND): $(SOURCES)
	$(CXX) -MM $^ > $@
.cpp.o:
	$(CXX) $(CXX_FLAGS) -c $<
clean:
	rm -f *.o

