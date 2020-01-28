//Node class to implement a map
class Node {
public:
  String* key_;
  Object* value_;
  Node* next_;

  Node() {
    key_ = new String();
    value_ = new Object();
    next_ = NULL;
  }
  //Node contructor
  Node(String* key, Object* value) {
    key_ = key;
    value_ = value;
    next_ = NULL;
  }
  //Gets the key of this node
  //Returns: String*
  String* getKey() {
    return key_;
  }

  //Gets the value of this node
  //Returns: Object*
  Object* getValue() {
    return value_;
  }

  //Sets the value of this node
  void setValue(Object* value) {
    value_ = value;
  }

  //Gets the next node
  //Returns Node*
  Node* getNext(){
    return next_;
  }

  //Sets the next node to be linked
  void setNext(Node* next) {
    next_ = next;
  }
};
