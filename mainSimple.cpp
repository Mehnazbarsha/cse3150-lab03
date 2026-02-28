#include <iostream>
#include "linked_list.h"

using namespace std;

int main() {

    LinkedList linkedList;
    for (int i = 0; i < 5; i++)
        linkedList.insertInFront(i);

    cout << linkedList << endl;
    linkedList.traverseList();

    LinkedList copy(linkedList);
    cout << copy << endl;

    LinkedList lst2;
    for (int v : {-1, 1, 1, -1, 3})
        lst2.insertAtEnd(v);
    cout << lst2 << endl;
    cout << "Size: " << lst2.getSize() << endl;
    cout << "Value at pos 2: " << lst2.getValueAt(2) << endl;

    lst2.deleteNodeNumber(0);
    cout << lst2 << endl;

    LinkedList pos;
    for (int v : {1, 2, 3, 4}) pos.insertAtEnd(v);
    cout << pos << endl;
    cout << "isPositivePrefixSum: " << (pos.isPositivePrefixSum() ? "true" : "false") << endl;
    cout << "isNegativePrefixSum: " << (pos.isNegativePrefixSum() ? "true" : "false") << endl;

    LinkedList neg;
    for (int v : {-1, -2, -3}) neg.insertAtEnd(v);
    cout << neg << endl;
    cout << "isPositivePrefixSum: " << (neg.isPositivePrefixSum() ? "true" : "false") << endl;
    cout << "isNegativePrefixSum: " << (neg.isNegativePrefixSum() ? "true" : "false") << endl;

    LinkedList pj;
    for (int v : {-1, 1, 1, -1, 5}) pj.insertAtEnd(v);
    pj.copyAllNodesAddresses();
    pj.printAllNodeAddresses();
    pj.printTableNodesNextValue();
    pj.runPointerJumps();
    pj.printTableNodesNextValue();

    return 0;
}