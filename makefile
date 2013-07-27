CC=g++
CFLAGS=-g -Wall -O3
PROGRAM=peflow
SOURCES=commandlineparser.cpp pedata.cpp peengine.cpp peflowmain.cpp
INCLUDES=.
LIBS=-lpthread

default: $(PROGRAM)

$(PROGRAM): $(SOURCES) commandlineparser.h ehm.h pedata.h peengine.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I $(INCLUDES) $(LIBS)
    
clean:
	rm -f $(PROGRAM)
