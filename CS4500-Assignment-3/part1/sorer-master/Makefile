all: build

build: 
	g++ -o sorer -std=c++11 main.cpp

clean:
	rm sorer

test:
	-./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0
	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 2
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 0
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 1
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 2
	./sorer -f "data.sor" -from 0 -len 100 -print_col_idx 2 0
	./sorer -f "data.sor" -from 5 -len 100 -print_col_idx 1 0
	./sorer -f "sor.txt" -from 0 -len 100 -print_col_type 0
	./sorer -f "sor.txt" -from 0 -len 100 -print_col_type 4
	./sorer -f "sor.txt" -from 0 -len 100 -print_col_type 2
	./sorer -f "sor.txt" -from 0 -len 100 -is_missing_idx 2 0
	./sorer -f "sor.txt" -from 0 -len 100 -is_missing_idx 2 1
	./sorer -f "sor.txt" -from 0 -len 100 -is_missing_idx 2 2
	./sorer -f "sor.txt" -from 0 -len 100 -print_col_idx 2 0
	./sorer -f "sor.txt" -from 0 -len 100 -print_col_idx 4 2
	./sorer -f "sor.txt" -from 5 -len 100 -print_col_idx 1 0

.PHONY: test
