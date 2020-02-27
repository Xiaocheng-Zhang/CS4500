TARGETS=server client

FILES=Makefile server.cpp client.cpp

CXXFLAGS=-Wall -std=c++11

# Rules

all: $(TARGETS)

$(TARGETS): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(TARGETS)
	./server &
	./client

clean:
	rm -fv *~ $(TARGETS) a.out

socket-example.zip: $(FILES)
	zip $@ $^
