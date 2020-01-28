#pragma once
#include "object.h"
#include <stdlib.h>
#include <stdbool.h>


/**
 * @brief Represents an array-structured list
 * 
 */
class Array {
public:

	/**
	 * @brief pushes the given object onto array
	 * 
	 * @param o the given object to be added
	 */
	void append(Object o);

	/**
	 * @brief removes all elements from array
	 * 
	 */
	void clear();

	/**
	 * @brief checks if the given object is in array
	 * 
	 * @param o object to be checked
	 * @return true if object in array
	 * @return false if object not in array
	 */
	bool contains(Object o);

	/**
	 * @brief duplicates array with all elements
	 * 
	 * @return Array cloned array
	 */
	Array copy();

	/**
	 * @brief retrieves the object at given position
	 * 
	 * @param idx index position
	 * @return Object object located at given index inside array
	 */
	Object get(size_t idx);

	/**
	 * @brief adds the given object to array at given position
	 * 
	 * @param o given object
	 * @param idx index position
	 */
	void insert(Object o, size_t idx);

	/**
	 * @brief deletes the given object from array
	 * 
	 * @param o object to be deleted
	 * @return Object removed object, now unlinked from array
	 */
	Object remove(Object o);

	/**
	 * @brief computes the length of array
	 * 
	 * @return size_t number of elements in array
	 */
	size_t size();

};