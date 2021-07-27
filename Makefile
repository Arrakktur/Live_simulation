CC = g++
SOURCE = a.cpp location.cpp animal.cpp eat.cpp object.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE = simulation

all: simulation

simulation: a.o location.o animal.o eat.o object.o
	$(CC) a.o location.o animal.o eat.o object.o -o $(EXECUTABLE)

a.o:
	$(CC) -c a.cpp

location.o:
	$(CC) -c location.cpp

animal.o:
	$(CC) -c animal.cpp

eat.o:
	$(CC) -c eat.cpp

object.o:
	$(CC) -c object.cpp