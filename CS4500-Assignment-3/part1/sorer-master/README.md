## Part 1 - Data Adapter

Taking in a Schema-on-Read which is in a row format and adapting it to be used at our "company". Our company takes in
data as a columnar representation. To make the data work for our company we have implemented a data adapter that works 
as follows.

The user can pass the following flags to the program:
- "f" (file_to_read)
- "from" (starting_byte)
- "len" (bytes_to_read)
- "print_col_type" (col)
- "print_col_idx" (col, row)
- "print_is_missing_idx" (col, row)

"make build" can be used to compile our program, "make test" can be used to run our premade tests, and "make clean"
can be used to rm the executable.

Additionally, our sorer program can be run using commands similar to the following

The following are examples of running
./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0
./sorer -f "data.sor" -from 0 -len 100 -print_col_type 2
./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 0
./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 1
./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 2
./sorer -f "data.sor" -from 0 -len 100 -print_col_idx 2 0
./sorer -f "data.sor" -from 5 -len 100 -print_col_idx 1 0

Note that only 1 of "print_col_type", "print_col_idx", and "print_is_missing_idx" can be used as a flag
 
The main workflow of our program can be described as follows.

1) getopt_long_only() is used to parse user input and that data is stored in flags.
2) The program determines the schema and datatypes by reading the first 500 lines in the file
3) Datatypes are stored as int constants with 0 representing BOOL, 1 representing INT,
   2 representing FLOAT, and 3 representing STRING
4) Using either the default values or passed in flags, the program begins reading the file
   starting from the given first byte and continuing until the specified number of bytes to
   read
5) As the file is read, columns are stored in a series of c++ vectors tracked by another vector,
   storing data for the whole file
6) Using the read data, the program performs the action specified by the final passed in flag
