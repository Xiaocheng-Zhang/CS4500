m := map_test
a := array_test
q := queue_test

all: clean $(m)

$(m):
	g++ -o $(m) -g -std=c++11 test-map.cpp

clean:
	rm -f $(m)