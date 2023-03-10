#include "HashTable.h"

HashTable::HashTable():
    size(127),
    elemNum()
{
    try {
        this->arr = new shared_ptr<AVLTree<UpTree, int>>[this->size];
        for (int i = 0; i < this->size; i++) {
            this->arr[i] = shared_ptr<AVLTree<UpTree, int>>(new AVLTree<UpTree, int>());
        }
    }
    catch(const std::bad_alloc& e) {
        throw std::bad_alloc();
    }
}

HashTable::~HashTable() {
    delete[] this->arr;
}

void HashTable::add(shared_ptr<UpTree> tree) {
    float newLoadFactor = (this->getElemNum() + 1) / float(this->getSize());
    try{
        if (newLoadFactor >= 0.7) {
            int newSize = 2 * (this->getSize() + 1) - 1;
            shared_ptr<AVLTree<UpTree, int>>* newArr = new shared_ptr<AVLTree<UpTree, int>>[newSize];
            for (int k = 0; k < newSize; k++) {
                newArr[k] = shared_ptr<AVLTree<UpTree, int>>(new AVLTree<UpTree, int>());
            }
            
            for (int i = 0; i < this->getSize(); i++){
                shared_ptr<AVLTree<UpTree, int>> curr = this->getArray()[i];
                TreeNode<UpTree, int>** tempArr = new TreeNode<UpTree, int>*[curr->getSize()]; 
                AVLTree<UpTree, int>::treeToArray(tempArr, curr->root, 0);

                for (int j = 0; j < curr->getSize(); j++){
                    shared_ptr<UpTree> curr = tempArr[j]->data;
                    int pos = hashFunction(curr->getPlayerId(), newSize);
                    newArr[pos]->insert(curr, curr->getPlayerId());
                }
                delete[] tempArr;
                //delete curr;
            }

            //shared_ptr<AVLTree<UpTree, int>> temp = this->arr;
            //delete[] temp;
            //delete[] this->arr;
            this->setArray(newArr);
            this->setSize(newSize);
        }

        int pos = hashFunction(tree->getPlayerId(), this->getSize());
        this->getArray()[pos]->insert(tree, tree->getPlayerId());
    }
    catch(const std::exception& e){
        delete[] this->arr;
        throw e;
    }
    this->elemNum++;
    
}

shared_ptr<UpTree> HashTable::find(int playerId) {
    int pos = hashFunction(playerId, this->getSize());
    /*if(this->getArray()[pos].root == nullptr) {
        //throw AVLTree<UpTree, int>::NodeNotFound();
        throw std::exception();
    }*/
    try {
        return this->getArray()[pos]->find(playerId);
    }
    catch(const std::exception& e) {
        throw e;
    }
}

int HashTable::getSize() const {
    return this->size;
}

int HashTable::getElemNum() const {
    return this->elemNum;
}

void HashTable::addElemNum(int num) {
    this->elemNum += num;
}

shared_ptr<AVLTree<UpTree, int>>* HashTable::getArray() const {
    return this->arr;
}

void HashTable::setArray(shared_ptr<AVLTree<UpTree, int>>* arr) {
    delete[] this->arr;
    this->arr = arr;
}

void HashTable::setSize(int size) {
    this->size = size;
}