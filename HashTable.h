#ifndef HashTable_h
#define HashTable_h

#include "UpTree.h"

class HashTable {

    private:
    
        int size;
        int elemNum;
        AVLTree<UpTree, int>* arr;

    public:
        HashTable();

        ~HashTable();

        HashTable(const HashTable& other) = default;
        
        HashTable& operator=(const HashTable& other) = default;
        
        static int hashFunction(const int& id, int size){
            return id % size;
        };

        void add(shared_ptr<UpTree> tree);

        shared_ptr<UpTree> find(int playerId);
        
        int getElemNum() const;

        void addElemNum(int num);

        int getSize() const;

        AVLTree<UpTree, int>* getArray() const; 
        
        void setArray(AVLTree<UpTree, int>* arr);

        void setSize(int size);
};

#endif