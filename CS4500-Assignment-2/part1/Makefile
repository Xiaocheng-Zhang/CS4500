m := map_test
a := array_test
q := queue_test

all: clean $(m) $(q) $(a) test

$(m):
	g++ -o $(m) -g -std=c++11 test-map.cpp

$(a):
	g++ -o $(a) -g -std=c++11 test-array.cpp

$(q):
	g++ -o $(q) -g -std=c++11 test-queue.cpp

clean:
	rm -f $(m)
	rm -f $(a)
	rm -f $(q)

test:
	./$(m)
	./$(q)
	./$(a)

