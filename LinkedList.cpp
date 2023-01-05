#include "LinkedList.h"

LinkedList::LinkedList():
data(),
next()
{}

LinkedList::LinkedList(shared_ptr<UpTree> tree):
data(tree),
next()
{}

LinkedList::~LinkedList() {
    LinkedList* curr = this;
    while(curr != nullptr) {
        LinkedList* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LinkedList::insert(shared_ptr<UpTree> tree) {
    LinkedList* curr = this;
    while (curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = new LinkedList(tree);
}

shared_ptr<UpTree> LinkedList::find(int playerId) {
    LinkedList* curr = this;
    while (curr != nullptr){
        if (this->data != nullptr) {
            if (this->data->getPlayerId() == playerId) {
                return this->data;
            }
        }
        curr = curr->next;
    }
    return nullptr;
}

shared_ptr<UpTree> LinkedList::getData() {
    return this->data;
}

LinkedList* LinkedList::getNext() {
    return this->next;
}