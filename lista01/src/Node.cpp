#include "Node.h"

// Constructor
Node::Node(float coeff, int deg)
    : coefficient(coeff), degree(deg), next(nullptr) {}

// Getters
float Node::getCoefficient() const { return coefficient; }
int Node::getDegree() const { return degree; }
Node *Node::getNext() const { return next; }
