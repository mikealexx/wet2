#ifndef WET2_LINKEDLIST_H
#define WET2_LINKEDLIST_H

#include "UpTree.h"

class LinkedList {

private:
    shared_ptr<UpTree> data;
    LinkedList* next;

public:

    LinkedList();

    LinkedList(shared_ptr<UpTree> tree);

    ~LinkedList();

    void insert(shared_ptr<UpTree> tree);

    shared_ptr<UpTree> find(int playerId);

    shared_ptr<UpTree> getData();

    LinkedList* getNext();
};

#endif //WET2_LINKEDLIST_H
