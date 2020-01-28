#include "object.h"

class Queue : public Object {
    public:
        // list of Objects
        Object** q;
        size_t size_;
        size_t capacity_;
        size_t hash_;

        Queue() : Object() {
            size_ = 0;
            capacity_ = 2;
            q = new Object*[capacity_];
            hash();
        }

        void fillWithNullPtr(int start) {
            for (int i = start; i < capacity_; i++) {
                q[i] = nullptr;
            }
        }

        void enlargeSize() {
            capacity_ = capacity_ * 2;
            Object** tmp = new Object*[capacity_];
            for (int i = 0; i < size_; i++) {
                tmp[i] = q[i];
            }
            delete[] q;
            q = tmp;

            fillWithNullPtr(size_);
        }

        /**
        *  adds an object to the end of this queue
        */
        void enqueue(Object* o) {
            if (size_ == capacity_) {
                enlargeSize();
            }
            q[size_] = o;
            size_++;
        }

        /**
        *  Pops the first object in this queue
        */
        Object* dequeue() {
            Object *result = q[0];
            Object** tmp = new Object*[capacity_];
            for (int n = 1; n < size_; n++) {
                tmp[n-1] = q[n];
            }
            delete[] q;
            q = tmp;
            size_ = size_ - 1;
            return result;
        }

        /**
        * Returns the first object in this queue without removing.
        */
        Object* peek() {
            return q[0];
        }

        /**
        * Returns the size of this queue.
        */
        size_t size() {
            return size_;
        }

        size_t hash() {
            if (size_ == 0) {
                hash_ = (size_t) this;
                return hash_;
            }
            hash_ = 0;
            for (int i = 0; i < size_; i++) {
                hash_ += q[i]->hash();
            }
            return hash_;
        }

        bool equals(Object* other) {
            Queue *oq = dynamic_cast<Queue*>(other);
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

        // const char* to_string() {
        //     return "";
        // }

};

