#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <ctype.h>

#include "cmdline.h"
#include "utility.h"
#include "dataframe.h"

using namespace std;

int main(int argc, char** argv) {
    // read in command line for configuration
    Configuration* config = new Configuration(argc, argv);
    if (config->parse() != 0) {
        delete config;
        Utility::quit("Usage: ./sorer \
            <-f input_file> \
            [-from start_pos] \
            [-len bytes_to_read] \
            [-print_col_type col_type | -print_col_idx idx offset | -is_missing_idx idx offset]");
    }

    DataFrame* data_frame = new DataFrame(config);
    int status_code = data_frame->parse();
    if (status_code == -1) {
        delete data_frame;
        Utility::quit("Failed to detect schema in input file");
    }
    
    char output_buffer[255] = {0};
    data_frame->run(output_buffer);
    cout << output_buffer << endl;
    delete data_frame;

    return 0;
}