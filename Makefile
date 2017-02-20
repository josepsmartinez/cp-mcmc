INCLUDE = inc/
SOURCE = src/
OBJECTS = obj/
BINARIES = bin/

CC = g++
CFLAGS = -Wall -fpermissive

compile_source: $(SOURCE)generator.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $(SOURCE)*.cpp
	mv *.o $(OBJECTS)
	
build_lib: compile_source
	ar -cvq libmcsamplegen.a $(OBJECTS)*.o
	mv *.a $(BINARIES)

compile_exec: build_lib
	$(CC) $(CFLAGS) -o exec $(SOURCE)instantiator.cpp -I $(INCLUDE) -L $(BINARIES) -lmcsamplegen 

run: compile_exec
	./exec

clean:
	rm -f $(OBJECTS)*.o $(BINARIES)*.a exec