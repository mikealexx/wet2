#include "HashTable.h"

int HashTable::hashFunction(int id) const {
    return id % this->arr.getSize();
}

void HashTable::add(UpTree* tree) {
    float newLoadFactor = (this->arr.getElemNum() + 1) / this->arr.getSize();

    if (newLoadFactor >= 0.7) {
        DynamicArray newArr = this->arr.resize();
        
    }
}

float HashTable::getLoadFactor() const {
    return this->arr.getLoadFactor();
}