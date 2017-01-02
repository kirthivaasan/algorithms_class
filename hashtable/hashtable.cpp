#include <iostream>
#include <functional> // for std::hash
#include "hashtable.h"

namespace kirthi 
{

// PUBLIC methods ------------------------------------------------------------------------------------------------------------------------------------
template <class Key, class Value>
hashtable<Key, Value>::hashtable() : _size(0), _capacity(1), num_collisions(0) {
    array = new Pair<Key, Value>[_capacity];
    //std::cout << "Constructed an array of Pairs with Default capacity 5" << std::endl;
    //std::cout << "Size: " << _size << "  Capacity: " << _capacity << std::endl;
}

template <class Key, class Value>
hashtable<Key, Value>::hashtable(size_t reserve_size) : _size(0), _capacity(reserve_size), num_collisions(0) {
    array = new Pair<Key, Value>[reserve_size];
    //std::cout << "Constructed an array of Pairs with capacity: " << reserve_size << std::endl;
    //std::cout << "Size: " << _size << "  Capacity: " << _capacity << std::endl;
}

template <class Key, class Value>
hashtable<Key, Value>::~hashtable() {
    clear();
}

template <class Key, class Value>
size_t hashtable<Key, Value>::size() {
    return _size;
}

template <class Key, class Value>
bool hashtable<Key, Value>::contains(const Key& key) {
    size_t hash = std::hash<Key>()(key);
    size_t index = hash % _capacity;
    for (size_t count = 1; count <= _capacity; count++) { // count = [0..._capacity-1] stops at _capacity - 1.
        if (array[index].pair_is_set && array[index].key == key) {
            return true; // key exists, do not insert again, do not do probing
        }
        index = index + (count * count);
        index = index % _capacity; // to make sure we never access an index that is out of bounds of the array.
    }
    return false;
}

template <class Key, class Value>
void hashtable<Key, Value>::insert(const Key& key, const Value& value) {
    /* 1. Find hash value of key
       2. modulo the hash by the size of array  (index)
       3. IF the bucket key is NULL, create and place inside the bucket a new Pair<Key,Value>(key, value)
        ELSE (that is if the bucket is already occupied), then resolve the collision, with QUADRATIC PROBING (this will be implemented later)
    */
    size_t hash = std::hash<Key>()(key);
    size_t index = hash % _capacity;
    if (_size - 2 == _capacity) resize(); // not necessary, but speeds up performance
    for (size_t count = 1; count <= _capacity; count++) { // count = [0..._capacity-1] stops at _capacity - 1.
        if (array[index].pair_is_set && array[index].key == key) {
            array[index].value = value; // update value
            return; // key exists, do not insert again, do not do probing
        }
        if (!array[index].pair_is_set) {
            array[index].key = key;
            array[index].value = value;
            array[index].pair_is_set = true;
            _size++;
            return;
        }
        num_collisions++;
        index = index + (count * count);
        index = index % _capacity; // to make sure we never access an index that is out of bounds of the array.
    }
    resize();
    insert(key, value); // try inserting again after resizing
}

template <class Key, class Value>
void hashtable<Key, Value>::remove(const Key& key) {
    // remove doesn't downsize the array, might consider implementing this later on
    size_t hash = std::hash<Key>()(key);
    size_t index = hash % _capacity;
    for (size_t count = 1; count <= _capacity; count++) { // count = [0..._capacity-1] stops at _capacity - 1.
        if (array[index].pair_is_set && array[index].key == key) {
            array[index].pair_is_set = false;
            _size--;
            return;
        }
        index = index + (count * count);
        index = index % _capacity; // to make sure we never access an index that is out of bounds of the array.
    }
}

template <class Key, class Value>
Value hashtable<Key, Value>::get(const Key& key) {
    size_t hash = std::hash<Key>()(key);
    size_t index = hash % _capacity;
    for (size_t count = 1; count <= _capacity; count++) { // count = [0..._capacity-1] stops at _capacity - 1.
        if (array[index].pair_is_set && array[index].key == key) {
            return array[index].value; // key exists, do not insert again, do not do probing
        }
        index = index + (count * count);
        index = index % _capacity; // to make sure we never access an index that is out of bounds of the array.
    }
    throw 1; // could not find key, throw error
}

template <class Key, class Value>
void hashtable<Key, Value>::print() {
    std::cout << "KEYS\t\tVALUES" << std::endl;
    std::cout << "====\t\t======" << std::endl;
    for (int i = 0; i < _capacity; i++) {
        if (array[i].pair_is_set) {
            std::cout << array[i].key << "\t\t" << array[i].value << std::endl;
        }
    }
}

template <class Key, class Value>
void hashtable<Key, Value>::clear() {
    delete[] array;
    array = nullptr;
}

// PRIVATE methods ------------------------------------------------------------------------------------------------------------------------------------
template <class Key, class Value>
size_t hashtable<Key, Value>::hash() {
    
}

template <class Key, class Value>
void hashtable<Key, Value>::resize() {
    // scary way of doing this
    //std::cout << "resize()" << std::endl;
    Pair<Key, Value> *old_array = array;
    size_t old_capacity = _capacity;
    _capacity = _capacity * 2;
    
    array = new Pair<Key, Value>[_capacity];
    for (size_t i = 0; i < old_capacity; i++) {
        if (old_array[i].pair_is_set)
            insert(old_array[i].key, old_array[i].value);
    }
    
    delete[] old_array;
    old_array = nullptr;
}


} // end namespace kirthi