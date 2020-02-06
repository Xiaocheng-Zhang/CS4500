V := valgrind --leak-check=full
S := > error.txt 2>&1

danyth := CS4500A1P1-master/
BryceZhic := A3Prize-master/submission/part1
nullptr := cs4500-assignment-1-master/
b := software-dev-data-parser-master/
rotwang.ai := swd_assignment_3-master/
segfault := sorer-master/

ADDRESS := /mnt/d/DOCUMENTS/CS4500/CS4500-Assignment-3/part1/

team1:
	rm -f sorer
	cd $(BryceZhic) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)
	

team2:
	rm -f sorer
	cd $(nullptr) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)

team3:
	rm -f sorer
	cd $(danyth) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)

team4:
	rm -f sorer
	cd $(b) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)

team5:
	rm -f sorer
	cd $(rotwang.ai) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)

team6:
	rm -f sorer
	cd $(segfault) && make
	mv sorer $(ADDRESS)sorer
	cd $(ADDRESS)


	
1:
	$(V) ./sorer -f 0.sor -print_col_type 0 $(S)
2:
	$(V) ./sorer -f 0.sor -is_missing_idx 0 0 $(S)
3: 
	$(V) ./sorer -f 1.sor -print_col_type 0 $(S)
4:
	$(V) ./sorer -f 1.sor -is_missing_idx 0 1 $(S)
5:
	$(V) ./sorer -f 1.sor -print_col_idx 0 3 $(S)
6:
	$(V) ./sorer -f 2.sor -print_col_type 0 $(S)
7:
	$(V) ./sorer -f 2.sor -print_col_type 1 $(S)
8:
	$(V) ./sorer -f 2.sor -print_col_type 2 $(S)
9:
	$(V) ./sorer -f 2.sor -print_col_type 3 $(S)
10:     
	$(V) ./sorer -f 2.sor -is_missing_idx 1 0 $(S)
11:
	$(V) ./sorer -f 2.sor -is_missing_idx 1 1 $(S)
12:
	$(V) ./sorer -f 2.sor -print_col_idx 3 0 $(S)
13:
	$(V) ./sorer -f 2.sor -print_col_idx 3 1 $(S)
14:
	$(V) ./sorer -f 2.sor -print_col_idx 2 0 $(S)
15:
	$(V) ./sorer -f 2.sor -print_col_idx 2 1 $(S)
16:
	$(V) ./sorer -f 3.sor -print_col_type 4 $(S)
17:
	$(V) ./sorer -f 3.sor -print_col_idx 2 10 $(S)
18:
	$(V) ./sorer -f 3.sor -print_col_idx 2 384200 $(S)
19:
	$(V) ./sorer -f 4.sor -print_col_idx 0 1 $(S)
20:
	$(V) ./sorer -f 4.sor -print_col_idx 0 2 $(S)
21:
	$(V) ./sorer -f 4.sor -print_col_idx 1 1 $(S)
22:
	$(V) ./sorer -f 4.sor -print_col_idx 1 2 $(S)
23:
	$(V) ./sorer -f 1.sor -from 1 -len 74 -print_col_type 0 $(S)
24:
	$(V) ./sorer -f 1.sor -from 1 -len 74 -is_missing_idx 0 0 $(S)
25:
	$(V) ./sorer -f 1.sor -from 1 -len 74 -print_col_idx 0 6 $(S)


test: #clean
	-./sorer -f 0.sor -print_col_type 0  
	-./sorer -f 0.sor -is_missing_idx 0 0
	-./sorer -f 1.sor -print_col_type 0  
	-./sorer -f 1.sor -is_missing_idx 0 1
	-./sorer -f 1.sor -print_col_idx 0 3
	-./sorer -f 2.sor -print_col_type 0
	-./sorer -f 2.sor -print_col_type 1
	-./sorer -f 2.sor -print_col_type 2
	-./sorer -f 2.sor -print_col_type 3
	-./sorer -f 2.sor -is_missing_idx 1 0
	-./sorer -f 2.sor -is_missing_idx 1 1
	-./sorer -f 2.sor -print_col_idx 3 0
	-./sorer -f 2.sor -print_col_idx 3 1
	-./sorer -f 2.sor -print_col_idx 2 0
	-./sorer -f 2.sor -print_col_idx 2 1
	-./sorer -f 3.sor -print_col_type 4
	-./sorer -f 3.sor -print_col_idx 2 10
	-./sorer -f 3.sor -print_col_idx 2 384200
	-./sorer -f 4.sor -print_col_idx 0 1
	-./sorer -f 4.sor -print_col_idx 0 2
	-./sorer -f 4.sor -print_col_idx 1 1
	-./sorer -f 4.sor -print_col_idx 1 2
	-./sorer -f 1.sor -from 1 -len 74 -print_col_type 0
	-./sorer -f 1.sor -from 1 -len 74 -is_missing_idx 0 0
	-./sorer -f 1.sor -from 1 -len 74 -print_col_idx 0 6

clean:
	- rm -f sorer

