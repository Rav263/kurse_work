CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp ./libs/table_io.cpp ./algs/linary_search.cpp ./algs/radix_tree.cpp ./algs/patricia_tree.cpp ./algs/avl_tree.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ip_routing

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ip_routing ./libs/*.o ./algs/*.o main.o
