#include <iostream>
#include "linked_list.h"

using namespace std;

int passed = 0;
int failed = 0;

#define ASSERT_EQ(a, b, msg) \
    do { \
        if ((a) == (b)) { cout << "[PASS] " << msg << endl; passed++; } \
        else { cout << "[FAIL] " << msg << " (got " << (a) << ", expected " << (b) << ")" << endl; failed++; } \
    } while(0)

#define ASSERT_TRUE(expr, msg)  ASSERT_EQ((expr), true, msg)
#define ASSERT_FALSE(expr, msg) ASSERT_EQ((expr), false, msg)

void test_insertInFront() {
    LinkedList l;
    l.insertInFront(10);
    ASSERT_EQ(l.getSize(), 1, "insertInFront size==1");
    ASSERT_EQ(l.getValueAt(0), 10, "insertInFront val==10");
    l.insertInFront(20);
    ASSERT_EQ(l.getSize(), 2, "insertInFront size==2");
    ASSERT_EQ(l.getValueAt(0), 20, "insertInFront head==20");
    ASSERT_EQ(l.getValueAt(1), 10, "insertInFront second==10");
}

void test_insertAtEnd() {
    LinkedList l;
    l.insertAtEnd(1); l.insertAtEnd(2); l.insertAtEnd(3);
    ASSERT_EQ(l.getSize(), 3, "insertAtEnd size==3");
    ASSERT_EQ(l.getValueAt(0), 1, "insertAtEnd val[0]==1");
    ASSERT_EQ(l.getValueAt(2), 3, "insertAtEnd val[2]==3");
}

void test_firstLast() {
    LinkedList l;
    l.insertAtEnd(5); l.insertAtEnd(6); l.insertAtEnd(7);
    ASSERT_EQ(l.getFirstElement()->data, 5, "getFirstElement==5");
    ASSERT_EQ(l.getLastElement()->data, 7, "getLastElement==7");
    Node * tail = l.getLastElement();
    ASSERT_TRUE(tail->next == tail, "tail->next==tail");
}

void test_deleteNode() {
    LinkedList l;
    for (int v : {10, 20, 30, 40}) l.insertAtEnd(v);
    l.deleteNodeNumber(1);
    ASSERT_EQ(l.getSize(), 3, "delete middle: size==3");
    ASSERT_EQ(l.getValueAt(1), 30, "delete middle: val[1]==30");
    l.deleteNodeNumber(0);
    ASSERT_EQ(l.getSize(), 2, "delete head: size==2");
    ASSERT_EQ(l.getValueAt(0), 30, "delete head: new head==30");
    l.deleteNodeNumber(1);
    ASSERT_EQ(l.getSize(), 1, "delete tail: size==1");
    Node * tail = l.getLastElement();
    ASSERT_TRUE(tail->next == tail, "after delete tail: tail->next==tail");
    l.deleteNodeNumber(0);
    ASSERT_EQ(l.getSize(), 0, "delete only element: size==0");
}

void test_copyConstructor() {
    LinkedList original;
    for (int v : {1, 2, 3, 4, 5}) original.insertAtEnd(v);
    LinkedList copy(original);
    ASSERT_EQ(copy.getSize(), 5, "copy size==5");
    for (int i = 0; i < 5; i++)
        ASSERT_EQ(copy.getValueAt(i), original.getValueAt(i), "copy val matches at pos " + to_string(i));
    Node * tail = copy.getLastElement();
    ASSERT_TRUE(tail->next == tail, "copy tail->next==tail");
    ASSERT_TRUE(copy.getFirstElement() != original.getFirstElement(), "copy is deep");
}

void test_copyEmpty() {
    LinkedList empty;
    LinkedList copy(empty);
    ASSERT_EQ(copy.getSize(), 0, "copy of empty: size==0");
}

void test_positivePrefixSum() {
    LinkedList l;
    for (int v : {1, 2, 3}) l.insertAtEnd(v);
    ASSERT_TRUE(l.isPositivePrefixSum(), "1,2,3: positive");
    ASSERT_FALSE(l.isNegativePrefixSum(), "1,2,3: not negative");
    LinkedList l2;
    for (int v : {-1, 2, 3}) l2.insertAtEnd(v);
    ASSERT_FALSE(l2.isPositivePrefixSum(), "-1,2,3: not positive");
}

void test_negativePrefixSum() {
    LinkedList l;
    for (int v : {-1, -2, -3}) l.insertAtEnd(v);
    ASSERT_TRUE(l.isNegativePrefixSum(), "-1,-2,-3: negative");
    ASSERT_FALSE(l.isPositivePrefixSum(), "-1,-2,-3: not positive");
    LinkedList l2;
    for (int v : {-1, 1, -3}) l2.insertAtEnd(v);
    ASSERT_FALSE(l2.isNegativePrefixSum(), "-1,1,-3: not negative");
}

void test_pointerJumping() {
    LinkedList l;
    for (int v : {-1, 1, 1, -1, 5}) l.insertAtEnd(v);
    l.copyAllNodesAddresses();
    l.runPointerJumps();
    Node * tail = l.getLastElement();
    int n = l.getSize();
    for (int i = 0; i < n; i++) {
        Node * node = static_cast<Node *>(l.getAddressFromArray(i));
        ASSERT_TRUE(node->next == tail, "pointer jump: node " + to_string(i) + " -> tail");
    }
}

void test_getValueOutOfRange() {
    LinkedList l;
    l.insertAtEnd(42);
    ASSERT_EQ(l.getValueAt(5), -1, "out of range returns -1");
    ASSERT_EQ(l.getValueAt(-1), -1, "negative index returns -1");
}

void test_singleElement() {
    LinkedList l;
    l.insertAtEnd(99);
    ASSERT_EQ(l.getSize(), 1, "single element size==1");
    ASSERT_TRUE(l.getFirstElement() == l.getLastElement(), "first==last");
    Node * n = l.getFirstElement();
    ASSERT_TRUE(n->next == n, "single element points to itself");
}

int main() {
    test_insertInFront();
    test_insertAtEnd();
    test_firstLast();
    test_deleteNode();
    test_copyConstructor();
    test_copyEmpty();
    test_positivePrefixSum();
    test_negativePrefixSum();
    test_pointerJumping();
    test_getValueOutOfRange();
    test_singleElement();

    cout << "\nResults: " << passed << " passed, " << failed << " failed." << endl;
    return (failed == 0) ? 0 : 1;
}