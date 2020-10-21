#pragma once
#include <utility>
//DO NOT INCLUDE MAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM std::pair<TKey, TValue>(-11111, -11111)
typedef bool (*Condition)(TValue);
#define CAPACITY 256
class MapIterator;

typedef struct dllaNode{
    TElem data = NULL_TELEM;
    int next;
    int prev;
}dllaNode;

typedef struct dlla{
    int capacity;
    dllaNode *nodes;
    int head;
    int tail;
    int firstEmpty;
    int size;
}dlla;



class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
		dlla map;

	public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

    //keeps in the Map only those pairs whose value respects the given condition
    void filter(Condition cond);
    //where Condition is a function which takes as parameter a value and returns true or false depending on whether the value respects the condition.

	// destructor
	~Map();

	void resize();

};



