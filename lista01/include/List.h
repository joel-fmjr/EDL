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
    std::tuple<float, int> getValues(int degree) const;
    void changeNode(int currentDegree, float coefficient, int degree);
    Node *getNext(Node *node) const;
    int size() const;
    bool isEmpty() const;
    bool exists(int degree) const;
    void insert(float coefficient, int degree);
    void remove(int degree);
    void showALL(bool endl=true) const;
    int getDegree() const;
    Node *getHead() const;
    void evaluate(float x);
    std::string toString(float x=NAN) const;
    std::string formatPrecision(float coeff) const;

    List operator+(const List &other) const;
    List operator-(const List &other) const;
    List operator*(const List &other) const;
};

#endif // LIST_H
