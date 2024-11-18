#include "Node.h"

// Constructor
Node::Node(float coeff, int deg)
    : coefficient(coeff), degree(deg), next(nullptr) {}

// Getters
float Node::getCoefficient() const { return coefficient; }
int Node::getDegree() const { return degree; }
Node* Node::getNext() const { return next; }

// Setters
void Node::setCoefficient(float coeff) { coefficient = coeff; }
void Node::setDegree(int deg) { degree = deg; }
void Node::setNext(Node* nxt) { next = nxt; }
