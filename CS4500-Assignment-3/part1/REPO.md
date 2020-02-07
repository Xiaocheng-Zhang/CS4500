## Team 4:	
### Name: SnowySong

This team used Python to implement this Assignment.
They did saved data as column and call methods to get from the dest column.
No more redundant code, the structure is compressed and useful.
The whole program was implemented by one class with enums.

Their SoR types are defined by enums called "SoRTypes"
Class "SorInterpreter" is the main Object function that provided most methods to read and save data.

Their code runs fast and go through these steps:
1. Set the initial status for reading at first: Method: "__init__" in "class SorInterpreter" in 31 line.
2. Read the data by lines, get the schema during reading. Method: "__get_column_schema" in 101 line in sorer. "__itemize_sor_row" is the main method read the data in line 136.
3. Call parser to parse the required data follow the schema.

- Run time: 
```
Fast:
real    0m2.885s
user    0m1.313s
sys     0m1.281s

Slow:
real    0m3.097s
user    0m1.297s
sys     0m1.500s

- Test failed:
./sorer -f 2.sor -print_col_idx 2 1
-.2 | -0.2
./sorer -f 4.sor -print_col_idx 1 1
-0.000000002 | -2e-09
./sorer -f 4.sor -print_col_idx 1 2
10000000000 | 1e+10
```

- For failed tests, they are subtle problems which are not problems. It is easy to handle these cases by update their "args.print_col_type" method with more type checker in 229 in sorer.
- In contrast to other groups' work, this program has many advantages:
  - It has simplified methods, which reduced redundant code.
  - Has many comments that help readers understand the whole program.
- However, they used python. They don't need to handle most problems.
- This program is ran on Windows subsystem Linux system:
  
  - product: AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx
  - vendor: Advanced Micro Devices [AMD]
  - physical id: 1
  - bus info: cpu@0
  - capacity: 2100MHz
  - width: 64 bits


## Team 5: 	
### Name: rotwang.ai

This team used C++ to implement this Assignment.
They designed six different header files, which forms a dataframe that help to write and read data.
Their code is clear in main.cpp file. Names of methods are readable. Total processes of this program are logical and readable. Each method has a comment that helped reader to understand. 

SoR types are saved as *enum* in *token.h* file

Code speed is median (tend to fast) and goes these steps:
1. Create a Configuration class that takes argc and argv, automatically parse the command and saved.
2. Create a dataframe class within saved configuration, generate the schema and save all data. If it cannot find a valid schema, the program will quit with error message.
   1. They saved all data by "vector<vector<Datatype>>", a 2D Array that saved data into inner array as one column.
   2. Their method "parse" will  able to push parsed data into their dataframe.
3. They will call *run* method in dataframe to print the data follow the configuration which saved commands in previous steps.

- Run time:
```
Fast:
real    0m12.731s
user    0m10.344s
sys     0m7.484s

Slow:
real    0m13.486s
user    0m10.563s
sys     0m7.844s

- Test failed:
./sorer -f 1.sor -print_col_idx 0 3
+1
./sorer -f 2.sor -print_col_idx 3 0
hi
./sorer -f 3.sor -print_col_idx 2 10
+1.2
./sorer -f 4.sor -print_col_idx 0 1
+2147483647
./sorer -f 4.sor -print_col_idx 1 1
-0.000000002
./sorer -f 1.sor -from 1 -len 74 -print_col_idx 0 6
+2.2
```

- Those failed tests are caused by *run* method in dataframe, it dose not print the data follow the schema.
- For different data types, they need print chosen data as the format that match them.

- Memory Usage:
	These are data came from running *sorer* by *Valgrind*:
```
==2066== HEAP SUMMARY:
==2066==     in use at exit: 48 bytes in 2 blocks
==2066==   total heap usage: 39 allocs, 37 frees, 1,082,374 bytes allocated
	==2066== 24 bytes in 1 blocks are definitely lost in loss record 1 of 2

	==2066== LEAK SUMMARY:
==2066==    definitely lost: 48 bytes in 2 blocks
==2066==    indirectly lost: 0 bytes in 0 blocks
==2066==      possibly lost: 0 bytes in 0 blocks
==2066==    still reachable: 0 bytes in 0 blocks
==2066==         suppressed: 0 bytes in 0 blocks

	==2066== 24 bytes in 1 blocks are definitely lost in loss record 1 of 2
==2066==    at 0x4835DEF: operator new(unsigned long) (vg_replace_malloc.c:334)
==2066==    by 0x10C23D: analyze_tokens_for_schema (schema.h:54)
==2066==    by 0x10C23D: analyze_for_schema (dataframe.h:229)
==2066==    by 0x10C23D: DataFrame::parse() (dataframe.h:122)
==2066==    by 0x10A38E: main (main.cpp:27)

	==2066== 24 bytes in 1 blocks are definitely lost in loss record 2 of 2
==2066==    at 0x4835DEF: operator new(unsigned long) (vg_replace_malloc.c:334)
==2066==    by 0x10AF7A: Token::tokenize_line(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) (token.h:214)
==2066==    by 0x10C966: process (dataframe.h:94)
==2066==    by 0x10C966: DataFrame::parse() (dataframe.h:158)
==2066==    by 0x10A38E: main (main.cpp:27)
```
- From *Valgrind* output, program's total Heap memory took 1,082,374 bytes, with 39 allocs. However, their code did not free all allocs after ending program.
  - Two memory lost happen in *parse* method in file datafram.h:94.
  - Vector in Token class wasn't freed.
- The Memory Usage of this program is *7 level* out of 10.

  - product: AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx
  - vendor: Advanced Micro Devices [AMD]
  - physical id: 1
  - bus info: cpu@0
  - capacity: 2100MHz
  - width: 64 bits
