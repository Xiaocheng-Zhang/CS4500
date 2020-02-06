#pragma once

const size_t MEGABYTE = 1000000;
const size_t BUFFER_SIZE = 1 * MEGABYTE;
const size_t LINE_RESERVE_CAP_SIZE = 128;

// Represents a buffer manager for file content
class ByteBuffer {
private:
    // file to read from [Responsible for closing]
    FILE* file;
    // index of first unread position in buffer
    size_t buffer_index = 0;
    // # of bytes currently written into buffer
    size_t bytes_in_buffer = 0;
    // total number of bytes read from given file
    size_t total_bytes_read = 0;
    // total number of bytes to be read
    size_t total_bytes_to_read = 0;
    // buffer for file contents, owned
    char* buffer = nullptr;

    // detects when end of file has been read
    bool is_eof() {
        return this->total_bytes_read == this->total_bytes_to_read;
    }

    // detects when buffer has been read, needs a refill
    bool is_end_of_buffer() {
        return this->buffer_index == this->bytes_in_buffer;
    }

    // fills buffer with file content
    // @returns bytes read
    size_t fill_buffer() {
        if (this->is_eof())
            return 0;

        size_t bytes_left_to_read = this->total_bytes_to_read - this->total_bytes_read;
        size_t bytes_to_read = min(bytes_left_to_read, BUFFER_SIZE);   

        this->bytes_in_buffer = fread(
            this->buffer, 
            sizeof(char), 
            bytes_to_read, 
            this->file
        );

        this->total_bytes_read += this->bytes_in_buffer; // increment by # read
        this->buffer_index = 0; // set back to 0
        return this->bytes_in_buffer;
    }

    // fetches next unread character from buffer
    // @returns nullptr when none remain, else pointer to char
    char* read_next_char() {
        if (this->is_end_of_buffer() && this->is_eof())
            return nullptr;

        // fill buffer if no bytes in buffer or read all content of this buffer
        if (this->total_bytes_read == 0 || this->is_end_of_buffer()) {
            // at end of buffer, refill with file content
            size_t bytes_read = this->fill_buffer();
            if (bytes_read == 0)
                return nullptr;
        }
        return this->buffer + (this->buffer_index++);
    }

public:
    ByteBuffer(FILE* file, size_t bytes_to_read) {
        assert(file != nullptr);
        this->file = file;
        this->total_bytes_to_read = bytes_to_read;
        this->buffer = new char[BUFFER_SIZE]; // allocate buffer
    }

    ~ByteBuffer() {
        fclose(this->file);
        delete[] this->buffer;
        this->buffer = nullptr;
    }

    // reads next line from file
    string* read_line() {
        // end of buffer & end of file, no more lines to be read
        if (this->is_end_of_buffer() && this->is_eof())
            return nullptr;

        char* current_char = nullptr;
        string* line = new string("");
        line->reserve(LINE_RESERVE_CAP_SIZE);
        while (current_char = this->read_next_char()) {
            *line += *current_char;
            if (*current_char == '\n' || *current_char == '\0')
                break;
        }

        if (line->size() == 0) {
            delete line;
            return nullptr; // no more characters to be read;
        }

        return line;
    }
};