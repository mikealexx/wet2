#ifndef HashTable_h
#define HashTable_h

#include "DynamicArray.h"

class HashTable {

    private:
    
        int size;
        int elemNum;
        float loadFactor;
        AVLTree<UpTree, int>* arr;

    public:
        HashTable();

        ~HashTable() = default;

        HashTable(const HashTable& other) = default;
        
        HashTable& operator=(const HashTable& other) = default;
        
        static int hashFunction(int id, int size){
            return id % size;
        };

        void add(shared_ptr<UpTree> tree);

        shared_ptr<UpTree> find(int playerId);

        float getLoadFactor() const;

        int getElemNum() const;

        int getSize() const;

        float getLoadFactor() const;

        AVLTree<UpTree, int>* getArray() const; 
        
        void setArray(AVLTree<UpTree, int>*& arr);

        void setSize(int size);
};

#endif