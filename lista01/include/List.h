#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <tuple>
#include <iostream>

class List
{
private:
    Node* head;
    Node* tail;
    int listSize;

    // Helper methods
    void copyFrom(const List& other);
    void clear();
    Node* searchDegree(int degree) const;

public:
    // Constructors and Destructor
    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    // Public interface
    std::tuple<float, int> getValues(Node *node) const;
    std::tuple<float, int> getValuesDegree(int degree) const;
    void changeNode(float coefficient, int degree);
    Node* getNext(Node* node) const;
    int size() const;
    bool isEmpty() const;
    bool exists(int degree) const;
    void insert(float coefficient, int degree);
    void removeDegree(int degree);
    void showAll() const;
    void print() const;
};

#endif // LIST_H
