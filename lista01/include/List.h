// include/List.h

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <tuple>

class List
{
private:
    // Nested Node class
    class Node
    {
    private:
        float coefficient;
        int degree;
        Node* next;

    public:
        Node(float coeff, int deg);
        // Getters
        float getCoefficient() const;
        int getDegree() const;
        Node* getNext() const;
        // Setters
        void setCoefficient(float coeff);
        void setDegree(int deg);
        void setNext(Node* nxt);

        // Friend class declaration
        friend class List;
    };

    Node* head;
    Node* tail;
    int listSize;

    // Helper methods
    void copyFrom(const List& other);
    void clear();

public:
    // Constructors and Destructor
    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    // Public interface
    std::tuple<float, int> getValues(int degree) const;
    void changeNode(float coefficient, int degree);
    int size() const;
    bool isEmpty() const;
    bool exists(int degree) const;
    void insert(float coefficient, int degree);
    void removeDegree(int degree);
    void deleteNode(Node* node);
    void print() const;

private:
    // Internal method to search for a node by degree
    Node* searchDegree(int degree) const;
};

#endif // LIST_H
