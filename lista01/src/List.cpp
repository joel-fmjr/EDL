#include "List.h"
#include <cmath>
#include <stdexcept>

// Implementation of Node class methods

// Constructor
List::Node::Node(float coeff, int deg)
    : coefficient(coeff), degree(deg), next(nullptr) {}

// Getters
float List::Node::getCoefficient() const { return coefficient; }
int List::Node::getDegree() const { return degree; }
List::Node* List::Node::getNext() const { return next; }

// Setters
void List::Node::setCoefficient(float coeff) { coefficient = coeff; }
void List::Node::setDegree(int deg) { degree = deg; }
void List::Node::setNext(Node* nxt) { next = nxt; }

// Implementation of List class methods

// Helper method to deep copy nodes
void List::copyFrom(const List& other)
{
    if (other.head == nullptr)
    {
        head = tail = nullptr;
        listSize = 0;
        return;
    }

    // Copy the head node
    head = new Node(other.head->coefficient, other.head->degree);
    listSize = 1;
    Node* currentOther = other.head->next;
    Node* currentThis = head;

    // Copy the rest of the nodes
    while (currentOther != nullptr)
    {
        Node* newNode = new Node(currentOther->coefficient, currentOther->degree);
        currentThis->next = newNode;
        currentThis = newNode;
        currentOther = currentOther->next;
        listSize++;
    }

    tail = currentThis;
}

// Helper method to delete all nodes
void List::clear()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    listSize = 0;
}

// Constructor
List::List()
    : head(nullptr), tail(nullptr), listSize(0) {}

// Copy Constructor
List::List(const List& other)
    : head(nullptr), tail(nullptr), listSize(0)
{
    copyFrom(other);
}

// Copy Assignment Operator
List& List::operator=(const List& other)
{
    if (this == &other)
        return *this;

    clear();
    copyFrom(other);
    return *this;
}

// Destructor
List::~List()
{
    clear();
}

// Internal method to search for a node by degree
List::Node* List::searchDegree(int degree) const
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->degree == degree)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Get the coefficient and degree as a tuple for a given degree
std::tuple<float, int> List::getValues(int degree) const
{
    Node* node = searchDegree(degree);
    if (node == nullptr)
        return {0.0f, 0};
    return {node->coefficient, node->degree};
}

// Change the coefficient of a node with a specific degree
void List::changeNode(float coefficient, int degree)
{
    Node* node = searchDegree(degree);
    if (node == nullptr)
    {
        std::cerr << "Degree " << degree << " not found. Inserting as new term.\n";
        insert(coefficient, degree);
        return;
    }

    node->coefficient = coefficient;

    if (node->coefficient == 0.0f)
    {
        removeDegree(degree);
    }
}

// Get the size of the list
int List::size() const
{
    return listSize;
}

// Check if the list is empty
bool List::isEmpty() const
{
    return head == nullptr;
}

// Check if a node with a specific degree exists
bool List::exists(int degree) const
{
    return searchDegree(degree) != nullptr;
}

// Insert a term into the list in sorted order
void List::insert(float coefficient, int degree)
{
    if (coefficient == 0.0f)
        return; // No need to store zero coefficient

    // Check if degree already exists and update coefficient if it does
    Node* existingNode = searchDegree(degree);
    if (existingNode != nullptr)
    {
        existingNode->coefficient += coefficient;
        if (existingNode->coefficient == 0.0f)
        {
            removeDegree(degree);
        }
        return;
    }

    // Create a new node
    Node* newNode = new Node(coefficient, degree);

    // Insert in descending order of degrees
    if (isEmpty() || head->degree < degree)
    {
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
            tail = newNode;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr && current->next->degree > degree)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == nullptr)
            tail = newNode;
    }

    listSize++;
}

// Remove a node with a specific degree from the list
void List::removeDegree(int degree)
{
    if (isEmpty())
        return;

    if (head->degree == degree)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
            tail = nullptr;
        listSize--;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->degree != degree)
    {
        current = current->next;
    }

    if (current->next != nullptr && current->next->degree == degree)
    {
        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail)
            tail = current;
        delete temp;
        listSize--;
    }
}

// Delete a node from the list (same as removeDegree)
void List::deleteNode(List::Node* node)
{
    // Delegate to removeDegree based on node's degree
    if (node != nullptr)
    {
        removeDegree(node->degree);
    }
}

// Print the polynomial
void List::print() const
{
    if (isEmpty())
    {
        std::cout << "0" << std::endl;
        return;
    }

    Node* node = head;
    bool first = true;
    while (node != nullptr)
    {
        float coeff = node->coefficient;
        int deg = node->degree;

        if (coeff == 0.0f)
        {
            node = node->next;
            continue;
        }

        // Handle sign
        if (coeff > 0 && !first)
            std::cout << " + ";
        else if (coeff < 0)
            std::cout << " - ";

        // Handle coefficient
        if (deg == 0 || std::abs(coeff) != 1.0f)
            std::cout << std::abs(coeff);

        // Handle variable and degree
        if (deg > 0)
        {
            std::cout << "x";
            if (deg > 1)
                std::cout << "^" << deg;
        }

        first = false;
        node = node->next;
    }
    std::cout << std::endl;
}
