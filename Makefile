INCLUDE = inc/
SOURCE = src/
OBJECTS = obj/
BINARIES = bin/

CC = g++
CFLAGS = -Wall -fpermissive

setup:
	mkdir $(OBJECTS) $(BINARIES)

clean:
	rm -f $(OBJECTS)*.o $(BINARIES)*.a exec 
	rm -f -r $(OBJECTS) $(BINARIES)

compile_source: $(SOURCE)generator.cpp clean setup
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $(SOURCE)*.cpp
	mv *.o $(OBJECTS)
	
build_lib: compile_source
	ar -cvq libmcsamplegen.a $(OBJECTS)*.o
	mv *.a $(BINARIES)

compile_exec: build_lib
	$(CC) $(CFLAGS) -o exec $(SOURCE)instantiator.cpp -I $(INCLUDE) -L $(BINARIES) -lmcsamplegen 

run: compile_exec
	./exec

full_test: compile_exec
	./exec 10 	1000 	1
	./exec 10 	10000 	1
	./exec 100 	1000 	1
	./exec 100 	10000 	1
	./exec 1000 	1000 	1
	./exec 1000 	10000 	1
	./exec 10 	1000 	2
	./exec 10 	10000 	2
	./exec 50 	1000 	2
	./exec 50 	10000 	2
	./exec 100 	1000 	2
	./exec 100 	10000 	2


