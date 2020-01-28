#include "object.h"
#include "node.h"

class Map {
public:
  //Size of the current map
  size_t len_;
  size_t capacity_;
  //Array of Node pointers in the map
  Node** elems_;

  //Constructor
  Map(){
    elems_ = NULL;
    capacity_ = 4;
    len_ = 0;
    initialize();
  }

  ~Map() {
    delete [] elems_;
  }

  /** initialize the map*/
  void initialize() {
  }

  //Adds an element to the map as a node pair
  void addElement(Node* elem) {
    Node** nodeArr = new Node* [len_ +1];
    if(elems_ == NULL) {
      nodeArr[len_] = elem;
    }
    else {
      for(size_t i = 0; i < len_; i++) {
        nodeArr[i] = elems_[i];
      }
      nodeArr[len_] = elem;
    }
    len_++;
    elems_ = nodeArr;
  }

  void put(Object *key) {

  }

  //Removed the given key from the map
  void removeElement(Object* key);


  //Gets the value of the key
  void getValue(Object* key);

  //Gets the length of the map
  void getLength();

  //Checks is the key is in the map
  bool isKeyIn(Object* e);
};
