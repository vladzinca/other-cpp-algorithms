CXX = g++

build:
	g++ -o curatare curatare.cpp
	g++ -o fortificatii fortificatii.cpp
	g++ -o beamdrone beamdrone.cpp

run-p1:
	./curatare

run-p2:
	./fortificatii

run-p3:
	./beamdrone

.PHONY: clean
clean :
	rm -f curatare fortificatii beamdrone
	rm -f *.out
