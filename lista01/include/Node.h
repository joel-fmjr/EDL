#ifndef NODE_H
#define NODE_H

class Node
{
private:
    float coefficient;
    int degree;
    Node *next;

public:
    // Constructor
    Node(float coeff, int deg);

    // Getters
    float getCoefficient() const;
    int getDegree() const;
    Node *getNext() const;

    friend class List;
};

#endif // NODE_H
