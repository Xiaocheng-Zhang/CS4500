1. Nullptr: 3.sor very slow √
2. the segfault in our stars:  √
```
./sorer -f 0.sor -print_col_type 0  
BOOL
./sorer -f 0.sor -is_missing_idx 0 0
1
./sorer -f 1.sor -print_col_type 0  
STRING
./sorer -f 1.sor -is_missing_idx 0 1
0
./sorer -f 1.sor -print_col_idx 0 3
+1
./sorer -f 2.sor -print_col_type 0
BOOL
./sorer -f 2.sor -print_col_type 1
INT
./sorer -f 2.sor -print_col_type 2
FLOAT
./sorer -f 2.sor -print_col_type 3
STRING
./sorer -f 2.sor -is_missing_idx 1 0
1
./sorer -f 2.sor -is_missing_idx 1 1
0
./sorer -f 2.sor -print_col_idx 3 0
hi
./sorer -f 2.sor -print_col_idx 3 1
ho ho ho
./sorer -f 2.sor -print_col_idx 2 0
1.2
./sorer -f 2.sor -print_col_idx 2 1
-0.2
./sorer -f 3.sor -print_col_type 4
BOOL
./sorer -f 3.sor -print_col_idx 2 10
1.2
./sorer -f 3.sor -print_col_idx 2 384200
1.2
./sorer -f 4.sor -print_col_idx 0 1
2147483647
./sorer -f 4.sor -print_col_idx 0 2
-2147483648
./sorer -f 4.sor -print_col_idx 1 1
-2e-09
./sorer -f 4.sor -print_col_idx 1 2
1e+10
./sorer -f 1.sor -from 1 -len 74 -print_col_type 0
STRING
./sorer -f 1.sor -from 1 -len 74 -is_missing_idx 0 0
0
./sorer -f 1.sor -from 1 -len 74 -print_col_idx 0 6
+2.2
```
3. ";<b>null</b>:
4. danyth:
5. rotwang.ai: 
6. BryceZhic: √ 没存