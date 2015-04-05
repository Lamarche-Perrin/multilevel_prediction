CC=g++
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=main.cpp markov_process.cpp voter_graph.cpp voter_experiment.cpp csv_tools.cpp partition.cpp timer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=multilevel_prediction

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
