## High-Level Design
### Program Start (relevant files: main.cpp, cmdline.h)
1. User specifies command line arguments which include a filename (non-optional), and start & stop index
2. this user input is given to a configuration class which performs validation on input, and makes it easier to access a decently high # of arguments cleanly
3. this configuration class is handed over to another class called DataFrame, which is responsible for
parsing file content, tokenizing, and saving data in an easy to access "columnar" format
### DataFrame (relevant files: data_frame.h, buffer.h)
1. Opens file, seeks to appropriate index in file (might be specified by user)
2. Hands file over to a ByteBuffer, a class that is responsible for managing 1 allocated buffer,
to be used to read in file contents, efficiently limiting the # of sys reads.
### More about ByteBuffer (relevant files: buffer.h)
1. Might be a case of re-inventing something that already exists, but based on test timing, is able
to outperform std::getline
### DataFrame continued (relevant files: data_frame.h)
1. reads each file line from ByteBuffer, tokenizes based on various rules specified in assignment, *DISCARDS* any line that contains malformed tokens
2. initially a pre-determined # of lines are read in order to detect the schema
3. if a schema is not determined, the program should exit
4. Once a schema is determined, the rest of the file content is tokenized, and only schema matches are able to be included in the final data vector
5. Post-parsing, an action, set in the configuration, will be executed, this output will be written to a buffer which is printed to STDOUT
### More on Schema Matching (relevant files: schema.h)
1. Schema::match(..) checks whether a series of tokens (one tokenized line of plaintext), matches a given vector of types
2. Rules: a NONE data_type matches any column type, and there must be at-least one match, if a given schema is longer than a given series of tokens, the series of tokens will be padded with None typed tokens