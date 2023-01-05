#ifndef HashTable_h
#define HashTable_h

#include "UpTree.h"
#include "DynamicArray.h"

class HashTable {

    private:
    
        DynamicArray arr;

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
        
        int getElemNum() const;

        int getSize() const;
};

#endif