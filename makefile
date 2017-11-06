CC = g++
CPPFLAGS = -std=c++0x
LIBS = -lpthread
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = hello_world

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(LIBS) $(SOURCES) -c

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
