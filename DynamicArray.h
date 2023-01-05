#ifndef DynamicArray_h
#define DynamicArray_h

#include "AVLTree.h"
#include "UpTree.h"
#include <memory>
using std::unique_ptr;

class DynamicArray {
    private:
        int size;
        int elemNum;
        float loadFactor;
        unique_ptr<AVLTree<UpTree, int>>* arr;

    public:
        DynamicArray();
        ~DynamicArray();

        void add(const shared_ptr<UpTree>& elem, int (*hash_func)(int, int));
        unique_ptr<AVLTree<UpTree, int>>& operator[](int i);

        int getSize() const;
        int getElemSize() const;

        void resize();

        class OutOfBounds : public std::exception{};
};

DynamicArray::DynamicArray():
    size(127),
    elemNum(0),
    loadFactor(0)
{
    this->arr = new unique_ptr<AVLTree<UpTree, int>>[this->size];
}

DynamicArray::~DynamicArray() {
    delete this->arr;
}

void DynamicArray::add(const shared_ptr<UpTree>& elem, int (*hash_func)(int, int)) {
    this->loadFactor = (this->elemNum + 1) / float(this->size);
    if(this->loadFactor >= 0.7) {
        this->resize();
    }
    int pos = hash_func(elem->getPlayerId(), this->size);
    if(this->arr[pos] == nullptr) {
        this->arr[pos] = unique_ptr<AVLTree<UpTree, int>>(new AVLTree<UpTree, int>());
    }
    this->arr[pos]->insert(elem, elem->getPlayerId());
    this->elemNum++;
}

unique_ptr<AVLTree<UpTree, int>>& DynamicArray::operator[](int i) {
    if(i < 0 || i >= this->size) {
        throw OutOfBounds();
    }
    return this->arr[i];
}

#endif //DynamicArray_h