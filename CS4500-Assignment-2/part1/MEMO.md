# Implementation explanation:

## Array implementation:
- In our implementation of array, we created four types of array to support 
int, float, bool, and String data types. 
- Some functions such as add, remove, clear are similar with what we designed for StringList. 
	* Array:
	


## Map implementation:
- For Map, we designed one extra class which pairs each key and value together in the map.
- Map is basically a list of key-value pairs.
- All essential methods such as put, get, isKeyIn have been implemented by us and all tests can be passed.

## Queue implementation:
- For Queue, we are able to support both String and Object because all functions take in Object and String is a child of object. 
- The essential methods such as enqueue, dequeue, peek have been implemented and examined by both spec tests and our own tests

# The critique of design and test:

	a) Array:
		1)Documentations of each method and test contained duplicated information 
		from method signatures. 
		2)The management team is very unresponsive. We, developer, have not heard
		any response from them via either Github or email for a week after we 
		post issue. Possibly we won't hear any from them even though we have 
		submitted the assignment. So we have decided to change the design and 
		test to meet those required functionalities.
		3)The tests given to us do not help at all. They have syntax issue everywhere. 
		Thus, we have to write whole tests by ourselves. We have edited the test with
		our own test cases in our Makefile.

		**UPDATE: 12 hours before deadline we heard their first reponse, which was 
		just an update on object.h and string.h.

	b) Map:
		1)Documentations are mostly in one line, which we as developers have to 
		guess what the management wants.
		2)The management team could response an issue within a day. The communication
		between us has been going well.
		3)Test quality has been improved by them after our request. The newest 
		version has been pretty comprehensive.

	c) Queue:
		1)Documentation is understandable in terms of methods' functionality.
		2)We can get their response in 1 or 2 days on average. 
		3)The amount of test is not sufficient. After we request more tests from 
		them, we have not heard any updates. They only have one test and our code 
		has passed that. Additionally, we also include our own test in Makefile. 
