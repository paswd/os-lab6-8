FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -pthread -lzmq
COMPILLER=g++

all: start

start: server.o client.o
	$(COMPILLER) $(FLAGS) -o server server.o
	$(COMPILLER) $(FLAGS) -o client client.o

server.o: testserver.cpp
	$(COMPILLER) -c $(FLAGS) -o server.o testserver.cpp

client.o: testclient.cpp
	$(COMPILLER) -c $(FLAGS) -o client.o testclient.cpp

clear:
	-rm -f *.o *.gch *.so server client

treetest: bintree.o testbintree.o
	$(COMPILLER) $(FLAGS) -o testbintree bintree.o testbintree.o

bintree.o: bintree.cpp
	$(COMPILLER) -c $(FLAGS) bintree.cpp

testbintree.o: testbintree.cpp
	$(COMPILLER) -c $(FLAGS) testbintree.cpp

