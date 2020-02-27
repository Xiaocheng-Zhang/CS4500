# Implementation explanation:

## Array implementation:
- In our implementation of array, we created four types of array to support 
int, float, bool, and String data types. 
- Some functions such as add, remove, clear are similar with what we designed for StringList. 
```
	Array:
	1. expand(): void //An Array constructor with initialized size, capacity, hashcode and Object list.
	2. append(size_t integer, Object *object: void //Append the object to the rest of array.
	3. clear(): void //clear the whole array elements.
	4. contains(Object *object): bool //check whether this array contains the input object.
	5. equals(Array *array): bool //check two array equal or not.
	6. get(size_t index): Object // get the element at index
	7. hash(): size_t //Returns the hash code value for this list.
	8. hash_me(): void //hash helper
	9. remove(size_t integer): Object //Removes the element at integer's index.
	10. size(): size_t //Return size of Array.
	11. add(size_t integer, Object *object): void //Add the object at index integer. Won't repace the element.
	Int_Array, Bool_Array, Float_Array:
	* The same methods' name, light difference in input type and return type. 
	* Functions are same.
```

## Map implementation:
- For Map, we designed one extra class which pairs each key and value together in the map.
- Map is basically a list of key-value pairs.
- All essential methods such as put, get, isKeyIn have been implemented by us and all tests can be passed.
```
	1. initialize(Node **temp): void //initialize the map
	2. hash_index(Object *key): size_t //hash the index of keys
	3. index_grow(size_t i): size_t //helper method to increase the index i in hash_put method
	4. index_check(size_t i, size_t index, size_t count): bool //check whether the loop needs end in hash_put method
	5. key_array(): Object** //return all keys as one array
	6. hash_put(Node **temp_elems, Object *key, Object *val): void //put key and val into temp_map
	7. expand(): void //expand the node array size
	8. addElement(Object *key, Object *value): void //Adds an element to the map as a node pair
	9. removeElement(Object *key): void //Removed the given key from the map
	10. getValue(Object *key): Object //Gets the value of the key
	11. getLength(): size_t //Gets the length of the map
	12. isKeyIn(Object *object) //Checks is the key is in the map
	13. contains(Node *node): bool //check does elems_ contains this node
	14. equals(Map *map): bool //check whether two maps are equal
	15. hash(): size_t //Return the hashcode
	16. hash_me(): void //hash helper
```

## Queue implementation:
- For Queue, we are able to support both String and Object because all functions take in Object and String is a child of object. 
- The essential methods such as enqueue, dequeue, peek have been implemented and examined by both spec tests and our own tests
```
	1. enlargeSize(): void //enlarge the size of the queue.
	2. fillWithNullPtr(int start): void //fill the object list with nullptr.
	3. enqueue(Object *o): void //adds an object to the end of this queue.
	4. dequeue(): Object* //Pops the first object in this queue
	5. peek(): Object* //Returns the first object in this queue without removing.
	6. size(): size_t //Returns the size of this queue.
	7. hash(): size_t //hash and return the hashcode.
	8. equals(Object *other): bool //check the two queue are equal.
```

# The critique of design and test:
* Array:
	1. Documentations of each method and test contained duplicated information 
		from method signatures. 
	2. The management team is very unresponsive. We, developer, have not heard
		any response from them via either Github or email for a week after we 
		post issue. Possibly we won't hear any from them even though we have 
		submitted the assignment. So we have decided to change the design and 
		test to meet those required functionalities.
	3. The tests given to us do not help at all. They have syntax issue everywhere. 
	Thus, we have to write whole tests by ourselves. We have edited the test with
	our own test cases in our Makefile.

	**UPDATE: 12 hours before deadline we heard their first reponse, which was just an update on object.h and string.h.**

* Map:
	1. Documentations are mostly in one line, which we as developers have to 
	guess what the management wants.
	2. The management team could response an issue within a day. The communication
	between us has been going well.
	3. Test quality has been improved by them after our request. The newest 
	version has been pretty comprehensive.

* Queue:
	1. Documentation is understandable in terms of methods' functionality.
	2. We can get their response in 1 or 2 days on average. 
	3. The amount of test is not sufficient. After we request more tests from 
	them, we have not heard any updates. They only have one test and our code 
	has passed that. Additionally, we also include our own test in Makefile. 
