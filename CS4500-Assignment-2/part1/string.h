#pragma once
// lang::CwC
#include "object.h"
#include <cassert>
#include <iostream>
/**
 * An immutable string class. Values passed in are copied and deleted
 * upon destruction.
 * author: vitekj@me.com
 */
class String : public Object {
public:
  char *val_;   // data
  size_t size_; // number of characters (excluding \0)

  /** Construct a string copying s */
  String(char *s) {
    size_ = strlen(s);
    val_ = duplicate(s);
  }

  /** Construct a string copying s */
  String(const char *s) {
    size_ = strlen(s);
    val_ = duplicate(s);
  }

  /** This constructor takes ownership of the char* s. The char*
   *  will be delete with the string. Use with caution. The first
   *  argument is there to differentiate this constructor from the
   *  standard one. */
  String(bool steal, char *s) {
    assert(steal);
    size_ = strlen(s);
    val_ = s;
  }

  /** Delete the string and free its data */
  ~String() { delete[] val_; }

  /** Compare strings for equality. */
  bool equals(Object *other) {
    if (other == nullptr)
      return false;
    String *tgt = dynamic_cast<String *>(other);
    if (tgt == nullptr)
      return false;
    return compare(tgt) == 0;
  }

  /** Returns 0 if strings are equal, >0 if this string is larger,
   *  <0 otherwise */
  int compare(String *tgt) { return strcmp(val_, tgt->val_); }

  /** Textbook hash function on strings.   */
  size_t hash_me_() {
    size_t hash = 0;
    for (size_t i = 0; i < size_; ++i)
      hash = val_[i] + (hash << 6) + (hash << 16) - hash;
    return hash;
  }

  /** Number of non \0 characters in this string */
  size_t size() { return size_; }

  /** Concatenate the strings, return a new object */
  String *concat(String *other) {
    char *res = new char[size_ + other->size() + 1];
    for (size_t i = 0; i < size_; i++)
      res[i] = val_[i];
    for (size_t i = size_, j = 0; i < size_ + other->size(); i++, j++) {
      res[i] = other->val_[j];
    }
    res[size_ + other->size()] = '\0';
    char* temp = strdup(res);
    delete [] res;
    return new String(temp);
  }

  /** Return a newly allocated char* with this string value */
  char *to_string() { return duplicate(val_); }

  /**
   * Prints this String
   */
  void print() { p("String(\"").p(val_).p("\")"); }

  /**
   * Removes leading and trailing spaces from this String
   */
  void trim() {
    char buf[size_];
    size_t i = 0;
    while (val_[i] == ' ') {
      i++;
    }
    size_t j = size_ - 1;
    while (val_[j] == ' ') {
      j--;
    }
    size_t k = 0;
    for (; i <= j; i++) {
      buf[k] = val_[i];
      k++;
    }
    buf[j + 1] = 0; 
    delete [] val_;
    val_ = strdup(buf);
  }

  /**
   * Returns a list of Strings split at the given separator.
   */
  String **split(char *separator) { return nullptr; }

  /**
   * Checks if this String contains the given String.
   */
  /**
   * Checks if this String contains the given String.
   */
  bool contains(String *sub) { 
    for (size_t i = 0; i < size_ - sub->size_; i++) {
      size_t j;
      for (j = 0; j < sub->size_; j++) {
        if (val_[i+j] != sub->val_[j]) {
          break;
        }
      }
      if (j == sub->size_) {
          return true;
      }
    }
    return false;
  }
};
