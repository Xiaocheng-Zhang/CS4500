all: clone build unzip run
unzip:
	unzip CS4500-as5-only-/datafile.zip
clear:
	rm -r CS4500-as5-only-
	rm -f datafile.txt
	rm -f bench
build:
	g++ -g -std=c++11 -o bench bench.cpp -lpthread
	
clone:
	git clone https://github.com/Xiaocheng-Zhang/CS4500-as5-only-.git

run: one two three
	
one:
	./bench datafile.txt regular

two:
	./bench datafile.txt TestRower

three:
	./bench datafile.txt AdvanceRower