CFLAGS=-c -Wall -Wextra -std=c++11

all : baris_yurdakul_1801042620

baris_yurdakul_1801042620 : main.o catalog.o 
	g++ main.o catalog.o -o baris_yurdakul_1801042620

main.o : main.cpp
	g++ $(CFLAGS) main.cpp

gates.o : catalog.cpp
	g++ $(CFLAGS) catalog.cpp
	
clean :
	rm -rf *o baris_yurdakul_1801042620
