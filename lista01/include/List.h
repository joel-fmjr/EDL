#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <tuple>
#include <iostream>
#include <cmath>

class List
{
private:
    Node *head;
    Node *tail;
    int listSize;

    // Helper methods
    void copyFrom(const List &other);
    void clear();
    Node *searchDegree(int degree) const;

public:
    // Constructors and Destructor
    List();
    List(const List &other);
    List &operator=(const List &other);
    ~List();

    // Public interface
    std::tuple<float, int> getValues(Node *node) const;
    std::tuple<float, int> getValuesDegree(int degree) const;
    void changeNode(float coefficient, int degree);
    Node *getNext(Node *node) const;
    int size() const;
    bool isEmpty() const;
    bool degreeExists(int degree) const;
    bool exists(Node *node) const;
    void insert(float coefficient, int degree);
    void removeDegree(int degree);
    void remove(Node *node);
    void showALL() const;
    int getDegree() const;
    Node *getHead() const;
    void printTerm(const Node *node, bool &first, float x = NAN) const;
    int getNumTerms() const;
    void evaluate(float x);

    List operator+(const List &other) const;
    List operator-(const List &other) const;
    List operator*(const List &other) const;
};

#endif // LIST_H
