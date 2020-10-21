#include "Map.h"
#include "MapIterator.h"

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity), O(capacity)
Map::Map() {
    this->map.capacity = CAPACITY;
    this->map.head = -1;
    this->map.tail = -1;
    this->map.firstEmpty = 0;
	this->map.size = 0;
	this->map.nodes = new dllaNode[this->map.capacity];

	for(int i = 0; i < this->map.capacity - 1; ++i)
	    this->map.nodes[i].next = i + 1;
	this->map.nodes[this->map.capacity - 1].next = -1;

    for(int i = map.capacity - 1; i > 0; --i)
        this->map.nodes[i].prev = i - 1;
    this->map.nodes[0].prev = -1;

}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
Map::~Map() {
	delete this->map.nodes;
}

// best case = Theta(1), worst case = Theta(numberOfElement), average case = Theta(numberOfElement), O(numberOfElement)
TValue Map::add(TKey c, TValue v){
    if(map.firstEmpty == -1)
        resize();
	if(this->size() == 0)
    {
	    this->map.nodes[this->map.firstEmpty].data.first = c;
        this->map.nodes[this->map.firstEmpty].data.second = v;
        this->map.nodes[this->map.firstEmpty].prev = -1;
        this->map.nodes[this->map.firstEmpty].next = -1;
        this->map.head = this->map.firstEmpty;
        this->map.tail = this->map.firstEmpty;
        this->map.size++;
        this->map.firstEmpty++;
        return NULL_TVALUE;
    }
	else
    {
        int current = this->map.head;
        while(current != -1  and this->map.nodes[current].data.first != c)
            current = this->map.nodes[current].next;
        if(current != -1)
        {
            int oldValue = this->map.nodes[current].data.second;
            this->map.nodes[current].data.second = v;
            return oldValue;
        }
        else
        {
            if(this->map.firstEmpty > this->map.tail)
            {
                this->map.nodes[this->map.firstEmpty].data.first = c;
                this->map.nodes[this->map.firstEmpty].data.second = v;
                this->map.nodes[this->map.firstEmpty].next = -1;
                this->map.nodes[this->map.firstEmpty].prev = this->map.tail;
                this->map.nodes[this->map.tail].next = this->map.firstEmpty;
                this->map.tail = this->map.firstEmpty;
                this->map.firstEmpty++;
                this->map.size++;
                return NULL_TVALUE;
            }
            else
            {
                this->map.nodes[this->map.firstEmpty].data.first = c;
                this->map.nodes[this->map.firstEmpty].data.second = v;
                this->map.firstEmpty = this->map.nodes[this->map.firstEmpty].next;
                this->map.nodes[this->map.firstEmpty].next = this->map.nodes[this->map.firstEmpty - 1].next;
                this->map.nodes[this->map.firstEmpty].prev = this->map.nodes[this->map.firstEmpty + 1].prev;
                this->map.size++;
                return NULL_TVALUE;
            }
        }
    }
}

// best case = Theta(1), worst case = Theta(numberOfElement), average case = Theta(numberOfElement), O(numberOfElement)
TValue Map::search(TKey c) const{
    int current = this->map.head;
    while(current != -1  and this->map.nodes[current].data.first != c)
        current = this->map.nodes[current].next;
    if(current != -1)
        return this->map.nodes[current].data.second;

    return NULL_TVALUE;
}

// best case = Theta(1), worst case = Theta(numberOfElement), average case = Theta(numberOfElement), O(numberOfElement)
TValue Map::remove(TKey c){
    if(this->size() == 0)
        return NULL_TVALUE;
    else
    {
        int current = this->map.head;
        while(current != -1  and this->map.nodes[current].data.first != c)
            current = this->map.nodes[current].next;
        if(current != -1)
        {
            int oldValue = this->map.nodes[current].data.second;
            if(current == this->map.tail)
            {
                this->map.nodes[this->map.nodes[current].prev].next = -1;
                this->map.tail = this->map.nodes[current].prev;
                this->map.nodes[current].prev = -1;
                this->map.nodes[current].next = this->map.firstEmpty;
                this->map.firstEmpty = current;
            }
            else if(current == this->map.head)
            {
                this->map.nodes[this->map.nodes[current].next].prev = -1;
                this->map.head = this->map.nodes[current].next;
                this->map.nodes[current].prev = -1;
                this->map.nodes[current].next = this->map.firstEmpty;
                this->map.firstEmpty = current;
            }
            else
            {
                this->map.nodes[this->map.nodes[current].prev].next = this->map.nodes[current].next;
                this->map.nodes[this->map.nodes[current].next].prev = this->map.nodes[current].prev;
                this->map.nodes[current].prev = -1;
                this->map.nodes[current].next = this->map.firstEmpty;
                this->map.firstEmpty = current;
            }
            this->map.size--;
            return oldValue;
        }

        else
            return NULL_TVALUE;
    }
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
int Map::size() const {
	if(this->isEmpty() == false)
	    return this->map.size;
	return 0;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool Map::isEmpty() const{
	if(this->map.size == 0)
	    return true;
	return false;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity), O(capacity)
void Map::resize()
{
    dllaNode * newNodes = new dllaNode[this->map.capacity * 2];
    for(int i = 0; i < this->map.capacity; ++i)
        newNodes[i] = this->map.nodes[i];
    for(int i = this->map.capacity; i < this->map.capacity * 2 - 1; ++i)
        newNodes[i].next = i + 1;
    newNodes[this->map.capacity - 1].next = -1;
    for(int i = this->map.capacity * 2 - 1; i > this->map.capacity; --i)
        newNodes[i].prev = i - 1;
    newNodes[this->map.capacity].prev = -1;
    delete this->map.nodes;

    this->map.nodes = newNodes;
    delete[] newNodes;
    this->map.firstEmpty = this->map.capacity + 1;
    this->map.capacity = this->map.capacity * 2;
}

// best case = Theta(numberOfElement), worst case = Theta(numberOfElement^2), average case = Theta(numberOfElement), O(numberOfElement^2)
void Map::filter(Condition cond)
{
    MapIterator it = iterator();
    while(it.valid())
    {
        if(!cond(it.getCurrent().second))
        {
            this->remove(it.getCurrent().first);
            it.first();
        }
        it.next();
    }
}



