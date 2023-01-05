#include "HashTable.h"

HashTable::HashTable():
    arr()
{}

void HashTable::add(shared_ptr<UpTree> tree) {
    this->arr.add(tree, *HashTable::hashFunction);
}

shared_ptr<UpTree> HashTable::find(int playerId) {
    int pos = hashFunction(playerId, this->getSize());
    if(this->arr[pos] == nullptr) {
        return nullptr;
    }
    try {
        return this->arr[pos]->find(playerId);
    }
    catch(const std::exception& e) { 
        throw e; //not found inside tree
    }
}

int HashTable::getSize() const {
    return this->arr.getSize();
}

int HashTable::getElemNum() const {
    return this->arr.getElemSize();
}