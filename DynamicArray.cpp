#include "DynamicArray.h"

DynamicArray::DynamicArray():
    size(127),
    elemNum(0),
    loadFactor(0)
{
    this->arr = new shared_ptr<AVLTree<UpTree, int>>[this->size];
}

DynamicArray::~DynamicArray() {
    delete[] this->arr;
}

void DynamicArray::add(const shared_ptr<UpTree>& elem, int (*hash_func)(int, int)) {
    this->loadFactor = (this->elemNum + 1) / float(this->size);
    if(this->loadFactor >= 0.7) {
        this->resize(hash_func);
    }
    int pos = hash_func(elem->getPlayerId(), this->size);
    if(this->arr[pos] == nullptr) {
        this->arr[pos] = shared_ptr<AVLTree<UpTree, int>>(new AVLTree<UpTree, int>());
    }
    this->arr[pos]->insert(elem, elem->getPlayerId());
    this->elemNum++;
}

shared_ptr<AVLTree<UpTree, int>>& DynamicArray::operator[](int i) {
    if(i < 0 || i >= this->size) {
        throw OutOfBounds();
    }
    return this->arr[i];
}

int DynamicArray::getSize() const {
    return this->size;
}

int DynamicArray::getElemSize() const {
    return this->elemNum;
}

void DynamicArray::resize(int (*hash_func)(int, int)) {
    this->size = 2 * (this->size + 1) - 1;
    shared_ptr<AVLTree<UpTree, int>>* newArr = new shared_ptr<AVLTree<UpTree, int>>[this->size];
    for(int i = 0; i < this->size; i++) {
        shared_ptr<AVLTree<UpTree, int>> curr = this->arr[i];
        TreeNode<UpTree, int>** tempArr = new TreeNode<UpTree, int>*[curr->getSize()];
        AVLTree<UpTree, int>::treeToArray(tempArr, curr->root, 0);
        for(int j = 0; j < curr->getSize(); j++) {
            shared_ptr<UpTree> currPlayer = tempArr[j]->data;
            int pos = hash_func(currPlayer->getPlayerId(), this->size);
            if(this->arr[pos] == nullptr) {
                this->arr[pos] = shared_ptr<AVLTree<UpTree, int>>(new AVLTree<UpTree, int>());
            }
            this->arr[pos]->insert(currPlayer, currPlayer->getPlayerId());
            this->elemNum++;
        }
        delete[] tempArr;
    }
    delete this->arr;
    this->arr = newArr;
}