FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -pthread -lzmq -std=c++11
COMPILLER=g++

all: start

start: server.o client.o converter.o note.o bintree.o
	$(COMPILLER) $(FLAGS) -o server converter.o note.o bintree.o server.o
	$(COMPILLER) $(FLAGS) -o client client.o

server.o: server.cpp
	$(COMPILLER) -c $(FLAGS) server.cpp

client.o: client.cpp
	$(COMPILLER) -c $(FLAGS) client.cpp

clear:
	-rm -f *.o *.gch *.so server client

treetest: bintree.o testbintree.o
	$(COMPILLER) $(FLAGS) -o testbintree bintree.o testbintree.o

bintree.o: bintree.cpp
	$(COMPILLER) -c $(FLAGS) bintree.cpp

testbintree.o: testbintree.cpp
	$(COMPILLER) -c $(FLAGS) testbintree.cpp

note.o: note.cpp
	$(COMPILLER) -c $(FLAGS) note.cpp

converter.o: converter.cpp
	$(COMPILLER) -c $(FLAGS) converter.cpp
