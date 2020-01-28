#include "object.h"

class Queue : public Object {
public:
  
  // list of Objects
  Object** q;
  
  
  /**
   *  adds an object to the end of this queue
   */
  void enqueue(Object* o) {
    
  }
  
  /**
   *  Pops the first object in this queue
   */
  Object* dequeue() {
    return nullptr;
  }
  
  /**
   * Returns the first object in this queue without removing.
   */
  Object* peek() {
    return nullptr;
  }
  
  /**
   * Returns the size of this queue.
   */
  size_t size() {
    return 0;
  }
  
  size_t hash() {
    return 0;
  }
  
  bool equals(Object* other) {
    return false;
  }
  
  const char* to_string() {
    return "";
  }
  
};
