CC = g++
CPPFLAGS = -std=c++0x -g
LIBS = -lpthread
SOURCES = $(addprefix src/, main.cpp)
MPSOURCES = $(addprefix src/, MPmain.cpp Printer.cpp ThreadPool.cpp)
OBJECTS = $(SOURCES:src/%.cpp=objects/%.o)
MPOBJECTS = $(MPSOURCES:src/%.cpp=objects/%.o)
EXECUTABLE = hello_world
MPEXECUTABLE = mp_hello_world

all: $(EXECUTABLE) $(MPEXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

$(MPEXECUTABLE): $(MPOBJECTS)
	$(CC) $(MPOBJECTS) $(LIBS) -o $@

objects/%.o: src/%.cpp
	$(CC) $(CPPFLAGS) $(LIBS) $(SOURCES) -c
	$(CC) $(CPPFLAGS) $(LIBS) $(MPSOURCES) -c
	mv *.o objects

clean:
	rm -f $(EXECUTABLE)* $(MPEXECUTABLE)* $(OBJECTS) $(MPOBJECTS)
