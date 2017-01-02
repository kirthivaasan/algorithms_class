/*
    @author Kirthivaasan
*/

/*
    hashtable a.k.a. dictionary.
    Uses std::hash() for getting hash of objects stored.
    Uses quadratic probing for collisions. 
    This is usually faster than chaining for several reasons:-
        -> Cache oblivious (because it stores elements in a single contiguous chunk)
        -> Does not requrire creating a constructing new linkedlists
           in each bucket (this is of course if you don't hardcode the lists)
*/

#ifndef hashtable_h
#define hashtable_h

typedef std::size_t size_t;

namespace kirthi {
    
template <class K, class V>
class Pair {
public:
    K key;
    V value;
    bool pair_is_set = false;
    //Pair(const K& key, const V& value) : key(key), value(value), is_set(true) {}
    //Pair() : pair_is_set(false) {}
};
    
template <class Key, class Value>
class hashtable {
public:
    hashtable();
    hashtable(size_t reserve_size);
    ~hashtable();
    size_t size();
    bool contains(const Key& key); // find whether the hashtable contains the key
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value get(const Key& key); // return the value of a given key, return NULL if key not found instead of raising an error like in Python
    void print();
    void clear();
    size_t getCollisions() {return num_collisions;}
private:
    size_t _size;
    size_t _capacity;
    Pair<Key, Value> *array;
    size_t num_collisions;
    void resize();
    size_t hash();
};

} // end namespace kirthi

#include "hashtable.cpp"
#endif