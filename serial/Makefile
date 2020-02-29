
executables=serial deserial
headers=misc.h

all: $(executables) 

$(executables): %: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean: 
	rm -f $(executables)

serial.zip: $(headers) serial.cpp deserial.cpp Makefile
	zip $@ $^

.PHONY: clean
