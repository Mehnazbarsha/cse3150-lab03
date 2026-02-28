#include <iostream>
#include <vector>
#include "linked_list.h"

using namespace std;

ostream & operator<<(ostream & os, const Node & node) {
    os << node.data;
    return os;
}

LinkedList::LinkedList() : root{nullptr} {}

LinkedList::LinkedList(const LinkedList & fromLL) {
    if (nullptr == fromLL.root) {
        root = nullptr;
        return;
    }
    root = new Node(fromLL.root->data);
    Node * currentOld = fromLL.root;
    Node * newList = root;
    while (currentOld != currentOld->next) {
        newList->next = new Node(currentOld->next->data);
        currentOld = currentOld->next;
        newList = newList->next;
    }
    newList->next = newList;
}

LinkedList::~LinkedList() {
    Node * current = root;
    if (nullptr != root) {
        while (current != current->next) {
            Node * nxt = current->next;
            delete current;
            current = nxt;
        }
        delete current;
    }
    root = nullptr;
}

void LinkedList::insertInFront(int _data) {
    Node * insertNode = new Node(_data);
    if (root) insertNode->next = root;
    root = insertNode;
}

void LinkedList::insertAtEnd(int val) {
    Node * newNode = new Node(val);
    if (!root) { root = newNode; return; }
    Node * current = root;
    while (current != current->next) current = current->next;
    current->next = newNode;
}

Node * LinkedList::getFirstElement() {
    return root;
}

Node * LinkedList::getLastElement() {
    if (!root) return nullptr;
    Node * current = root;
    while (current != current->next) current = current->next;
    return current;
}

int LinkedList::getSize() {
    if (!root) return 0;
    int size = 0;
    Node * current = root;
    while (current != current->next) { size++; current = current->next; }
    return size + 1;
}

int LinkedList::getValueAt(int position) {
    if (!root || position < 0) return -1;
    int count = 0;
    Node * current = root;
    while (current != current->next && count < position) {
        count++;
        current = current->next;
    }
    if (count == position) return current->data;
    return -1;
}

void LinkedList::deleteNodeNumber(int nodeNumber) {
    if (!root || nodeNumber < 0) return;
    if (nodeNumber == 0) {
        Node * temp = root;
        root = (root == root->next) ? nullptr : root->next;
        delete temp;
        return;
    }
    int count = 0;
    Node * lag = root;
    Node * current = root;
    while (current != current->next && count < nodeNumber) {
        count++;
        lag = current;
        current = current->next;
    }
    if (count == nodeNumber) {
        lag->next = (current == current->next) ? lag : current->next;
        delete current;
    }
}

void LinkedList::traverseList() {
    Node * current = root;
    while (current && current->next != current) {
        cout << static_cast<void *>(current) << " next: "
             << static_cast<void *>(current->next) << " data: " << current->data << endl;
        current = current->next;
    }
    if (current)
        cout << static_cast<void *>(current) << " next: "
             << static_cast<void *>(current->next) << " data: " << current->data << endl;
}

void LinkedList::printAllNodeAddresses() {
    for (auto address : nodeAddresses)
        cout << static_cast<void *>(address) << " ";
    cout << endl;
}

void LinkedList::printTableNodesNextValue() {
    cout << "Node address  next-ptr  data" << endl;
    for (auto address : nodeAddresses) {
        Node * n = static_cast<Node *>(address);
        cout << n << "  " << n->next << "  " << n->data << endl;
    }
}

void LinkedList::copyAllNodesAddresses() {
    nodeAddresses.clear();
    if (!root) return;
    Node * current = root;
    while (current != current->next) {
        nodeAddresses.push_back(static_cast<void *>(current));
        current = current->next;
    }
    nodeAddresses.push_back(static_cast<void *>(current));
}

void * LinkedList::getAddressFromArray(int i) {
    return static_cast<void *>(nodeAddresses[i]);
}

void LinkedList::pointerJump(Node * head) {
    if (head && head->next && head != head->next)
        head->next = head->next->next;
}

void LinkedList::runPointerJumps() {
    if (nodeAddresses.empty()) return;
    int rounds = 0;
    int tmp = (int)nodeAddresses.size();
    while (tmp > 1) { tmp >>= 1; rounds++; }
    rounds++;
    for (int r = 0; r < rounds; r++)
        for (auto address : nodeAddresses)
            pointerJump(static_cast<Node *>(address));
}

bool LinkedList::isPositivePrefixSum() {
    if (!root) return true;
    int sum = 0;
    Node * current = root;
    while (current != current->next) {
        sum += current->data;
        if (sum <= 0) return false;
        current = current->next;
    }
    return (sum + current->data) > 0;
}

bool LinkedList::isNegativePrefixSum() {
    if (!root) return true;
    int sum = 0;
    Node * current = root;
    while (current != current->next) {
        sum += current->data;
        if (sum >= 0) return false;
        current = current->next;
    }
    return (sum + current->data) < 0;
}

ostream & operator<<(ostream & os, const LinkedList & linkedList) {
    Node * current = linkedList.root;
    if (nullptr == linkedList.root) return os;
    while (current != current->next) {
        os << *current << " ";
        current = current->next;
    }
    os << *current;
    return os;
}