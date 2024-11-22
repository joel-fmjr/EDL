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

    // Helper methods (private)
    void clear();
    void copyFrom(const List &other);
    std::string formatPrecision(float coeff) const;
    std::string toString(float x = NAN) const;
    std::string toSuperscript(int degree) const;


public:
    List();
    List(const List &other);
    ~List();
    List &operator=(const List &other);

    void insert(float coefficient, int degree);
    void remove(int degree);
    bool exists(int degree) const;
    int size() const;
    bool isEmpty() const;
    Node *search(int degree) const;
    Node *getHead() const;
    Node *getNext(Node *node) const;
    std::tuple<float, int> getValues(int degree) const;

    int getDegree() const;
    void evaluate(float x);
    void showALL(bool endl = true) const;
    friend std::ostream &operator<<(std::ostream &os, const List &list);

    void changeNode(int currentDegree, float coefficient, int degree);

    List operator+(const List &other) const;
    List operator-(const List &other) const;
    List operator*(const List &other) const;
};

#endif // LIST_H
