#DECLARE THE VARIABLE
#CC=G++

#CFLAGS=-C  -WALL

run: main

main: BST.o Hash.o main.o
	g++ BST.o Hash.o main.o -o main

BST.o: BST.cpp
	g++ -c BST.cpp

Hash.o: Hash.cpp
	g++ -c Hash.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o main