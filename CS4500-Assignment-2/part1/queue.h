#pragma once
#include "object.h"

/**
 * Queue is a FIFO list.
 */
class Queue : public Object {
public:
  // list of Objects
  Object **q;
  size_t size_;
  size_t capacity_;
  size_t hash_;

  /**
   * queue constructor with initialized size, capacity and
   * Object list.
   */
  Queue() : Object() {
    size_ = 0;
    capacity_ = 2;
    q = new Object *[capacity_];
    hash();
  }

  /**
   * fill the object list with nullptr.
   * @param start start index of the method.
   */
  void fillWithNullPtr(int start) {
    for (int i = start; i < capacity_; i++) {
      q[i] = nullptr;
    }
  }

  /**
   * enlarge the size of the queue.
   */
  void enlargeSize() {
    capacity_ = capacity_ * 2;
    Object **tmp = new Object *[capacity_];
    for (int i = 0; i < size_; i++) {
      tmp[i] = q[i];
    }
    delete[] q;
    q = tmp;

    fillWithNullPtr(size_);
  }

  /**
   *  adds an object to the end of this queue.
   * @param o object that will be put into queue.
   */
  void enqueue(Object *o) {
    if (size_ == capacity_) {
      enlargeSize();
    }
    q[size_] = o;
    size_++;
  }

  /**
   *  Pops the first object in this queue
   *  @return return the first element into this queue.
   */
  Object *dequeue() {
    Object *result = q[0];
    Object **tmp = new Object *[capacity_];
    for (int n = 1; n < size_; n++) {
      tmp[n - 1] = q[n];
    }
    delete[] q;
    q = tmp;
    size_ = size_ - 1;
    return result;
  }

  /**
   * Returns the first object in this queue without removing.
   * @return return first object.
   */
  Object *peek() { return q[0]; }

  /**
   * Returns the size of this queue.
   * @return returns the size of this queue.
   */
  size_t size() { return size_; }

  /**
   * hash and return the hashcode.
   * @return return the hashcode.
   */
  size_t hash() {
    if (size_ == 0) {
      hash_ = (size_t)this;
      return hash_;
    }
    hash_ = 0;
    for (int i = 0; i < size_; i++) {
      hash_ += q[i]->hash();
    }
    return hash_;
  }

  /**
   * check the two queue are equal.
   * @param other other queue needed to be checked.
   * @return return true if they are equal.
   */
  bool equals(Object *other) {
    Queue *oq = dynamic_cast<Queue *>(other);
    if (!oq) {
      return false;
    }
    if (size_ != oq->size()) {
      return false;
    }
    if (size_ == oq->size()) {
      for (int i = 0; i < size_; i++) {
        if (!q[i]->equals(oq->q[i])) {
          return false;
        }
      }
    }
    return true;
  }
};
