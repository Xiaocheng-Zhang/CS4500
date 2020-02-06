#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream> 
#include <getopt.h>
#include <limits>

const int TYPE_BOOL = 0;
const int TYPE_INT = 1;
const int TYPE_FLOAT = 2;
const int TYPE_STRING = 3;

// determine which type str belongs to
int determine_type(char* str) {
  if (strcmp(str, "0") == 0 || strcmp(str, "1") == 0 || strcmp(str, "") == 0) {
    return TYPE_BOOL;
  }
  char* endptr = NULL;
  int num = strtol(str, &endptr, 10);
  //https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
  if (*endptr == 0) {
    return TYPE_INT;
  }
  //https://stackoverflow.com/questions/29169153/how-do-i-verify-a-string-is-valid-double-even-if-it-has-a-point-in-it
  auto result = float();
  auto i = std::istringstream(str);
  i >> result;      
  if (!i.fail() && i.eof()) {
    return TYPE_FLOAT;
  }
  return TYPE_STRING;
}
// convert a buffer to the given type
void* convert_to_type(int type, char* buf) {
  if (type == TYPE_BOOL) {
    if (strcmp(buf, "0") == 0) {
      return new bool(0);
    } else {
      return new bool(1);
    }
  }
  if (type == TYPE_INT) {
    return new int(atoi(buf));
  }
  if (type == TYPE_FLOAT) {
    auto result = float();
    auto i = std::istringstream(buf);
    i >> result;
    return new float(result);
  }
  if (type == TYPE_STRING) {
    size_t len = strlen(buf);
    char* dupl = new char[len + 1];
    strcpy(dupl, buf);
    return dupl;
  }
}

// print a data type according to const values
void print_data_types(uint print_col_type, std::vector<int>* data_types) {
  int t = data_types->at(print_col_type);
  if (t == TYPE_BOOL) {
    std::cout << "BOOL" << std::endl;
  }
  if (t == TYPE_INT) {
    std::cout << "INT" << std::endl;
  }
  if (t == TYPE_FLOAT) {
    std::cout << "FLOAT" << std::endl;
  }
  if (t == TYPE_STRING) {
    std::cout << "STRING" << std::endl;
  }
}

// print an index at a specific column
void print_col_idx(uint print_col_idx_col, 
                   uint print_col_idx_row, 
                   std::vector<int>* data_types, 
                   std::vector<std::vector<void*>*>* columns) {
  void* val = columns->at(print_col_idx_col)->at(print_col_idx_row);
  int t = data_types->at(print_col_idx_col);
  if (val == NULL) {
    std::cout << "NULL" << std::endl;
  }
  else if (t == TYPE_BOOL) {
    std::cout << *(bool*)val << std::endl;
  }
  else if (t == TYPE_INT) {
    std::cout << *(int*)val << std::endl;
  }
  else if (t == TYPE_FLOAT) {
    std::cout << *(float*)val << std::endl;
  }
  else if (t == TYPE_STRING) {
    std::cout << (char*)val << std::endl;
  }
}

// print whether a value is missing
void print_is_missing_idx(uint print_is_missing_idx_col, 
                           uint print_is_missing_idx_row, 
                           std::vector<std::vector<void*>*>* columns) {
    void* val = columns->at(print_is_missing_idx_col)->at(print_is_missing_idx_row);
    if (val == NULL) {
      std::cout << 1 << std::endl;
    } else {
      std::cout << 0 << std::endl;
    }
}

// handle command line options
void parse_command_line(int argc, 
                         char** argv,
                         char** f,
                         uint* from,
                         uint* len,
                         uint* print_col_type,
                         uint* print_col_idx_col,
                         uint* print_col_idx_row,
                         uint* print_is_missing_idx_col,
                         uint* print_is_missing_idx_row
) {
  int x;
  while(1) {
    static struct option long_options[] = {
      {"f",              required_argument, 0,  'f' },
      {"from",           required_argument, 0,  'b' },
      {"len",            required_argument, 0,  'c' },
      {"print_col_type", required_argument, 0,  'd' },
      {"print_col_idx",  required_argument, 0,  'e' },
      {"is_missing_idx", required_argument, 0,  'g' },
    };

    int option_index = 0;
    x = getopt_long_only(argc, argv, "f:b:c:d:e:g:", long_options, &option_index);
    if (x == -1) {
      break;
    }
    switch(x) {
      case 'f' :
        {
          char** tmp = new char*(optarg);
          *f = *tmp;
          break;
        }
      case 'b' :
        *from = atoi(optarg);
        break;
      case 'c' :
        *len = atoi(optarg);
        break;
      case 'd' :
        *print_col_type = atoi(optarg);
        break;
      case 'e' :
        *print_col_idx_col = atoi(optarg);
        break;
      case 'g' :
        *print_is_missing_idx_col = atoi(optarg);
        break;
    }
  }

  if (*print_col_idx_col != -1) {
    *print_col_idx_row = atoi(argv[optind]);
  } else if (*print_is_missing_idx_col != -1) {
    *print_is_missing_idx_row = atoi(argv[optind]);
  }
}

int main(int argc, char** argv) {
  //https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html

  char* f = "sor.txt";
  uint from = 0;
  uint len = std::numeric_limits<unsigned int>::max();
  uint print_col_type = -1;
  uint print_col_idx_col = -1;
  uint print_col_idx_row = -1;
  uint print_is_missing_idx_col = -1;
  uint print_is_missing_idx_row = -1;

  parse_command_line(argc, 
                     argv, 
                     &f, 
                     &from, 
                     &len, 
                     &print_col_type, 
                     &print_col_idx_col, 
                     &print_col_idx_row, 
                     &print_is_missing_idx_col, 
                     &print_is_missing_idx_row);

  char buf[256];
  size_t ind = 0;
  bool ignore_spaces = true;


  std::ifstream ifs;
  ifs.open(f, std::ifstream::in);

  // parse the first 500 lines to determine schema
  std::vector<char*>* cur_vector = new std::vector<char*>();
  std::vector<int> data_types;
  size_t cur_col = 0;
  size_t max_col = 0;
  size_t cur_row = 0;
  size_t max_row = 0;

  char c = ifs.get();
  while (ifs.good() && cur_row <= 500) {
    switch(c) {
      case '<' :
        ind = 0;
        break;
      case '>' :
        {
          buf[ind] = '\0';
          size_t len = strlen(buf);
          char* dupl = new char[len + 1];
          strcpy(dupl, buf);
          cur_vector->push_back(dupl);

          int t = determine_type(dupl);
          if (cur_col >= data_types.size()) {
            data_types.push_back(t);
          } else if (t > data_types[cur_col]) {
            data_types[cur_col] = t;
          }
          cur_col++;
          ind = 0;
          break;
        }
      case ' ' :
        if (!ignore_spaces) {
          buf[ind] = c;
          ind++;
        }
        break;
      case '\"' :
        ignore_spaces = !ignore_spaces;
        break;
      case '\n' :
        if (cur_col - 1 > max_col && cur_col != 0) {
          max_col = cur_col - 1;
          max_row = cur_row;
        }
        delete cur_vector;
        cur_vector = new std::vector<char*>();
        cur_col = 0;
        cur_row++;
        break;
      default :
        buf[ind] = c;
        ind++;
    }
    c = ifs.get();
  }
  ifs.close();
  ifs.clear();

  ifs.open(f, std::ifstream::in);
  
  // actually read file according to given parameters
  std::vector<std::vector<void*>*> columns;
  cur_col = 0;
  cur_row = 0;
  ind = 0;
  ignore_spaces = true;

  for (size_t i = 0; i <= max_col; i++) {
    columns.push_back(new std::vector<void*>());
  }

  if (from != 0) {
    ifs.ignore(from); 
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  c = ifs.get();
  size_t bytes_read = 1;

  while (ifs.good() && (bytes_read < len)) {
    switch(c) {
      case '<' :
        ind = 0;
        break;
      case '>' :
        {
          buf[ind] = '\0';
          if (strlen(buf) != 0) {
            columns[cur_col]->push_back(convert_to_type(data_types[cur_col], buf));
          } else {
            columns[cur_col]->push_back(NULL);
          }

          cur_col++;
          ind = 0;
          break;
        }
      case ' ' :
        if (!ignore_spaces) {
          buf[ind] = c;
          ind++;
        }
        break;
      case '\"' :
        ignore_spaces = !ignore_spaces;
        break;
      case '\n' :
        // fill a column until it reaches the max column length
        for (size_t i = cur_col; i <= max_col; i++) {
          columns[i]->push_back(NULL);
        }
        cur_col = 0;
        cur_row++;
        break;
      default :
        buf[ind] = c;
        ind++;
    }
    c = ifs.get();
    bytes_read++;
  }

  // delete any incomplete rows
  if (ifs.good()) {
    for (int i = 0; i < columns.size(); i++) {
      if (columns[i]->size() == cur_row - 1) {
        columns[i]->pop_back();
      }
    }
  }

  // print according to the given option
  if (print_col_type != -1) {
    print_data_types(print_col_type, &data_types);
  } else if (print_col_idx_col != -1) {
    print_col_idx(print_col_idx_col, print_col_idx_row, &data_types, &columns);
  } else if (print_is_missing_idx_col != -1) {
    print_is_missing_idx(print_is_missing_idx_col, print_is_missing_idx_row, &columns);
  }

  return 0;
}


