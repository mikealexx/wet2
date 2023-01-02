#include "AVLTree.h"
#include "UpTree.h"

class DynamicArray {
            private:
                int size;
                int elemNum;
                float loadFactor;
                AVLTree<UpTree, int>* array;
            public:
                DynamicArray():
                    size(127),
                    elemNum(),
                    loadFactor()
                {
                    try {
                        this->array = new AVLTree<UpTree, int>[this->size];
                    }
                    catch(const std::bad_alloc& e) {
                        throw std::bad_alloc();
                    }
                }

                DynamicArray(const DynamicArray& other) {
                    this->size = other.size;
                    this->elemNum = other.elemNum;
                    this->array = other.array;
                }

                DynamicArray& operator= (const DynamicArray& other) {
                    this->size = other.size;
                    this->elemNum = other.elemNum;
                    this->array = other.array;
                    return *this;
                }

                ~DynamicArray() {
                    delete[] array;
                }

                // Create a new dynamic array with the next size
                DynamicArray resize() {
                    DynamicArray out; 
                    out.size = 2 * (this->size + 1) - 1;
                    out.array = new AVLTree<UpTree, int>[out.size];
                    return out;
                }

                void add(int i, shared_ptr<UpTree> tree) {
                    this->array[i].insert(tree, tree->getPlayerId());
                    this->elemNum++;
                    this->loadFactor = elemNum / size;
                }

                AVLTree<UpTree, int> find(int i) {
                    return this->array[i];
                }

                int getElemNum() const {
                    return this->elemNum;
                }

                int getSize() const {
                    return this->size;
                }

                float getLoadFactor() const {
                    return this->loadFactor;
                }

                
        };