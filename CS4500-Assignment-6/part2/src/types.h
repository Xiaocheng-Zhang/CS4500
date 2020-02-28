#pragma once

const int STRING = 0;
const int INTEGER = 1;
const int FLOAT = 2;
const int BOOL = 3;
const int DOUBLE = 4;
const char *SERIALIZE_FORMAT = "%04d ";
const char CLASS_START = '{';
const char CLASS_END = '}';
const char CLASS_VAR_SEP = '|';
const char ARRAY_START = '[';
const char ARRAY_END = ']';
const int TYPE_OFFSET = 5;

const int STRING_ARRAY = 1000;
const int BOOL_ARRAY = 1001;