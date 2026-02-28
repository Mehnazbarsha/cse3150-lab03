#ifndef _NODE_H
#define _NODE_H

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node * next;

    Node() : data{0}, next{this}  {}
    Node(int _data) : data{_data}, next{this}  {}
};

ostream & operator<<(ostream & os, const Node & node);

#endif
