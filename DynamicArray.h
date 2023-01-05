#ifndef DynamicArray_h
#define DynamicArray_h

#include "AVLTree.h"
#include "UpTree.h"
#include <memory>
using std::shared_ptr;

class DynamicArray {
    private:
        int size;
        int elemNum;
        float loadFactor;
        shared_ptr<AVLTree<UpTree, int>>* arr;

    public:
        DynamicArray();
        ~DynamicArray();

        void add(const shared_ptr<UpTree>& elem, int (*hash_func)(int, int));
        shared_ptr<AVLTree<UpTree, int>>& operator[](int i);

        int getSize() const;
        int getElemSize() const;

        void resize(int (*hash_func)(int, int));

        class OutOfBounds : public std::exception{};
};

#endif //DynamicArray_h