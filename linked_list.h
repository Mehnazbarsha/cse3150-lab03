#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <iostream>
#include <vector>

#include "Node.h"

using namespace std;

class LinkedList {

    friend ostream & operator<<(ostream & os, const LinkedList & linkedList);

    Node * root;
    vector<void *> nodeAddresses;

    public:
        // constructors & destructor
        LinkedList();
        LinkedList(const LinkedList & fromLL);   // copy constructor
        ~LinkedList();

        void insertInFront(int _data);
        void insertAtEnd(int val);

        Node * getFirstElement();
        Node * getLastElement();
        int    getSize();
        int    getValueAt(int position);

        void deleteNodeNumber(int nodeNumber);

        void traverseList();
        void printAllNodeAddresses();
        void printTableNodesNextValue();

        void   copyAllNodesAddresses();
        void * getAddressFromArray(int i);

        void pointerJump(Node * head);
        void runPointerJumps();

        bool isPositivePrefixSum();  
        bool isNegativePrefixSum();   

};

#endif
