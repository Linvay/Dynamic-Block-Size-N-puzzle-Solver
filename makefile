CC = g++
CPPFLAGS = -g

SOURCE = GameState.cpp GameGraph.cpp
OBJ = $(SOURCE:.cpp=.o)

all: $(OBJ)
	$(CC) main_IDS.cpp $(OBJ) -o main_IDS
	$(CC) main_IDAStar.cpp $(OBJ) -o main_IDAStar

main: $(OBJ)
	$(CC) $^ -o $@

clean:
	del *.o