#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity), O(capacity)
SortedMap::SortedMap(Relation r) {
	this->sortedMap.capacity = CAPACITY;
    this->sortedMap.root = -1;
    this->sortedMap.firstEmpty = 0;
    this->sortedMap.length = 0;
    this->sortedMap.nodes = new BSTNode[this->sortedMap.capacity];
    this->relation = r;

    for (int i = 0; i < this->sortedMap.capacity - 1; i++)
        this->sortedMap.nodes[i].left = i + 1;
    this->sortedMap.nodes[this->sortedMap.capacity - 1].left = -1;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
TValue SortedMap::add(TKey k, TValue v) {
    if(this->sortedMap.length == this->sortedMap.capacity - 1)
        resize();
    if(this->size() == 0)
    {
        this->sortedMap.nodes[this->sortedMap.firstEmpty].data.first = k;
        this->sortedMap.nodes[this->sortedMap.firstEmpty].data.second = v;
        this->sortedMap.nodes[this->sortedMap.firstEmpty].right = -1;
        this->sortedMap.nodes[this->sortedMap.firstEmpty].left = -1;
        this->sortedMap.root = this->sortedMap.firstEmpty;
        this->sortedMap.length++;
        this->sortedMap.firstEmpty++;
        return NULL_TVALUE;
    }
    else
    {
        int current = this->sortedMap.root;
        int prev;
        while(current != -1 and this->sortedMap.nodes[current].data.first != k)
        {
            prev = current;
            if(this->relation(k, this->sortedMap.nodes[current].data.first))
                current = this->sortedMap.nodes[current].left;
            else
                current = this->sortedMap.nodes[current].right;
        }
        if(current != -1)
        {
            int oldValue = this->sortedMap.nodes[current].data.second;
            this->sortedMap.nodes[current].data.second = v;
            return oldValue;
        }
        else
        {
            current = this->sortedMap.firstEmpty;
            this->sortedMap.nodes[current].data.first = k;
            this->sortedMap.nodes[current].data.second = v;
            if(this->relation(k, this->sortedMap.nodes[prev].data.first))
                this->sortedMap.nodes[prev].left = current;
            else
                this->sortedMap.nodes[prev].right = current;

            this->sortedMap.firstEmpty = this->sortedMap.nodes[current].left;
            this->sortedMap.nodes[current].right = -1;
            this->sortedMap.nodes[current].left = -1;
            this->sortedMap.length++;
            return NULL_TVALUE;
        }
    }
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
TValue SortedMap::search(TKey k) const {
    int current = this->sortedMap.root;
    while(current != -1 and this->sortedMap.nodes[current].data.first != k)
    {
        if(this->relation(k, this->sortedMap.nodes[current].data.first))
            current = this->sortedMap.nodes[current].left;
        else
            current = this->sortedMap.nodes[current].right;
    }
    if(current != -1)
        return this->sortedMap.nodes[current].data.second;
	return NULL_TVALUE;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
TValue SortedMap::remove(TKey k) {
    if(this->size() == 0)
        return NULL_TVALUE;
    else
    {
        int current = this->sortedMap.root;
        int prev;
        while(current != -1  and this->sortedMap.nodes[current].data.first != k)
        {
            prev = current;
            if(this->relation(k, this->sortedMap.nodes[current].data.first))
                current = this->sortedMap.nodes[current].left;
            else
                current = this->sortedMap.nodes[current].right;
        }

        if(current != -1)
        {
            int oldValue = this->sortedMap.nodes[current].data.second;
            int left = this->sortedMap.nodes[current].left;
            int right = this->sortedMap.nodes[current].right;

            if(left == -1 and right == -1) {
                if (current == this->sortedMap.root)
                {
                    this->sortedMap.root = -1;
                }
                else
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = -1;
                    else
                        this->sortedMap.nodes[prev].right = -1;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }
            }
            else if(left != -1 and right == -1)
            {
                if (current == this->sortedMap.root)
                {
                    this->sortedMap.root = left;
                }
                else
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = left;
                    else
                        this->sortedMap.nodes[prev].right = left;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }
            }
            else if(left == -1 and right != -1)
            {
                if (current == this->sortedMap.root)
                {
                    this->sortedMap.root = right;
                }
                else
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = right;
                    else
                        this->sortedMap.nodes[prev].right = right;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }
            }
            else if(left != -1 and right != -1)
            {
                int min = 99999;
                current = this->sortedMap.nodes[current].right;
                while(current != -1)
                {
                    prev = current;
                    if(this->relation(k, this->sortedMap.nodes[current].data.first))
                        current = this->sortedMap.nodes[current].left;
                    else
                        current = this->sortedMap.nodes[current].right;
                    if(current < min)
                        min = current;
                }
                oldValue = this->sortedMap.nodes[min].data.second;
                left = this->sortedMap.nodes[min].left;
                right = this->sortedMap.nodes[min].right;

                if(left == -1 and right == -1)
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = -1;
                    else
                        this->sortedMap.nodes[prev].right = -1;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }
                else if(left != -1 and right == -1)
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = left;
                    else
                        this->sortedMap.nodes[prev].right = left;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }
                else if(left == -1 and right != -1)
                {
                    if(this->relation(this->sortedMap.nodes[current].data.first, this->sortedMap.nodes[prev].data.first))
                        this->sortedMap.nodes[prev].left = right;
                    else
                        this->sortedMap.nodes[prev].right = right;

                    this->sortedMap.nodes[current].left = this->sortedMap.firstEmpty;
                    this->sortedMap.firstEmpty = current;
                }

            }
            this->sortedMap.length--;
            return oldValue;
        }
        else
            return NULL_TVALUE;
    }
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
int SortedMap::size() const {
	return this->sortedMap.length;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool SortedMap::isEmpty() const {
    if (this->sortedMap.length == 0)
        return true;
    else
        return false;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
SortedMap::~SortedMap() {
    delete[] this->sortedMap.nodes;
}

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity), O(capacity)
void SortedMap::resize()
{
    BSTNode * newNodes = new BSTNode[this->sortedMap.capacity * 2];

    for(int i = 0; i < this->sortedMap.capacity; ++i)
        newNodes[i] = this->sortedMap.nodes[i];

    for(int i = this->sortedMap.capacity; i < this->sortedMap.capacity * 2 - 1; ++i)
        newNodes[i].left = i + 1;
    newNodes[this->sortedMap.capacity - 1].left = -1;


    this->sortedMap.nodes = newNodes;
    this->sortedMap.firstEmpty = this->sortedMap.capacity;
    this->sortedMap.capacity = this->sortedMap.capacity * 2;
}
