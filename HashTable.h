#ifndef HashTable_h
#define HashTable_h

#include "UpTree.h"
#include "LinkedList.h"

class HashTable {

    private:
    
        int size;
        int elemNum;
        LinkedList** arr;

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

        LinkedList** getArray() const;
        
        void setArray(LinkedList** arr);

        void setSize(int size);
};

#endif