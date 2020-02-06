#pragma once


class Debug {
public:
    static void print_token(Token* token) {
        if (token->value) {
            cout << *token->value;
        }
    }

    static void print_data(vector<vector<Token*>*>* data) {
        for (size_t i = 0; i < data->size(); i++) {
            for (size_t j = 0; j < data->at(i)->size(); j++) {
                print_token(data->at(i)->at(j));
                cout << " ";
            }
            cout << endl;
        }
    }

    // Debugging Tool
    static void print_tokens(vector<Token*>* vec) {
        for (size_t i = 0; i < vec->size(); i++) {
            Token* t = vec->at(i);
            cout << i << " " << "(" << DATA_TYPE_TO_STRING[t->type] << ")";
        }
        cout << endl;
    }    

        // Debugging tool
    static void print_token_types(vector<vector<Token*>*>* data) {
        for (size_t i = 0; i < data->size(); i++) {
            cout << i << " ";
            print_tokens(data->at(i));
        }
    }

    static void print_schema(vector<DataType>* vec) {
        for (size_t i = 0; i < vec->size(); i++) {
            cout << "(" << DATA_TYPE_TO_STRING[vec->at(i)] << ")";
        }
        cout << endl;
    }
};