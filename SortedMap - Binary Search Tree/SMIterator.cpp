#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
SMIterator::SMIterator(const SortedMap& m) : map(m){
    this->bst = m.sortedMap;
    int node = this->bst.root;
    while (node != -1)
    {
        this->stack.push(node);
        node = this->bst.nodes[node].left;
    }
    if (!this->stack.empty())
    {
        this->currentElement = this->stack.top();
    }
    else
        this->currentElement = -1;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
void SMIterator::first(){
    while (!this->stack.empty())
        this->stack.pop();
    int node = this->bst.root;
    while (node != -1)
    {
        this->stack.push(node);
        node = this->bst.nodes[node].left;
    }
    if (!this->stack.empty())
    {
        this->currentElement = this->stack.top();
    }
    else
        this->currentElement = -1;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
void SMIterator::next(){
    if (!this->valid())
        throw(exception());

    int node = this->stack.top();
    this->stack.pop();
    if (this->bst.nodes[node].right != -1)
    {
        node = this->bst.nodes[node].right;
        while (node != -1)
        {
            this->stack.push(node);
            node = this->bst.nodes[node].left;
        }
    }
    if (!this->stack.empty())
        this->currentElement = this->stack.top();
    else
        this->currentElement = -1;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool SMIterator::valid() const{
    if(this->currentElement != -1)
        return true;
    return false;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
TElem SMIterator::getCurrent() const{
    if (!this->valid())
        throw(exception());
    return this->bst.nodes[currentElement].data;
}


