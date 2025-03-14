F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
Z = ICS46_hw8.zip
P = graph

def: $P

main: dijkstras_main.cpp dijkstras.cpp dijkstras.h
	g++ $F dijkstras.cpp dijkstras_main.cpp -o main

ladder: ladder_main.cpp ladder.cpp ladder.h 
	g++ $F ladder.cpp ladder_main.cpp -o ladder

clean:
	/bin/rm -f $P $Z 

zip: clean
	zip $Z Makefile dijkstras_main.cpp dijkstras.h dijkstras.cpp ladder_main.cpp ladder.cpp ladder.h small.txt medium.txt large.txt largest.txt
