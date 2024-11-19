#include "List.h"

// Helper method to deep copy nodes
void List::copyFrom(const List &other)
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
    Node *currentOther = other.head->next;
    Node *currentThis = head;

    // Copy the rest of the nodes
    while (currentOther != nullptr)
    {
        Node *newNode = new Node(currentOther->coefficient, currentOther->degree);
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
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
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
List::List(const List &other)
    : head(nullptr), tail(nullptr), listSize(0)
{
    copyFrom(other);
}

// Copy Assignment Operator
List &List::operator=(const List &other)
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

// Internal method to get the next node
Node *List::getNext(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    return node->next;
}

// Internal method to search for a node by degree
Node *List::searchDegree(int degree) const
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->degree == degree)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Get the coefficient and degree as a tuple for a given degree
std::tuple<float, int> List::getValuesDegree(int degree) const
{
    Node *node = searchDegree(degree);
    if (node == nullptr)
        return {0.0f, 0};
    return {node->coefficient, node->degree};
}

// Get the coefficient and degree as a tuple for a given node
std::tuple<float, int> List::getValues(Node *node) const
{
    if (node == nullptr)
        return {0.0f, 0};
    return {node->coefficient, node->degree};
}

// Change the coefficient of a node with a specific degree
void List::changeNode(float coefficient, int degree)
{
    Node *node = searchDegree(degree);
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
bool List::degreeExists(int degree) const
{
    return searchDegree(degree) != nullptr;
}

// Check if a specific node exists
bool List::exists(Node *node) const
{
    Node *existingNode = searchDegree(node->degree);
    return existingNode == node;
}

// Insert a term into the list in sorted order
void List::insert(float coefficient, int degree)
{
    if (coefficient == 0.0f)
        return; // No need to store zero coefficient

    // Check if degree already exists and update coefficient if it does
    Node *existingNode = searchDegree(degree);
    if (existingNode != nullptr)
    {
        existingNode->coefficient += coefficient;
        if (existingNode->coefficient == 0.0f)
        {
            removeDegree(degree);
        }
        return;
    }

    Node *newNode = new Node(coefficient, degree);

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
        Node *current = head;
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
        Node *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
            tail = nullptr;
        listSize--;
        return;
    }

    Node *current = head;
    while (current->next != nullptr && current->next->degree != degree)
    {
        current = current->next;
    }

    if (current->next != nullptr && current->next->degree == degree)
    {
        Node *temp = current->next;
        current->next = temp->next;
        if (temp == tail)
            tail = current;
        delete temp;
        listSize--;
    }
}

void List::remove(Node *node)
{
    if (node == nullptr)
        return;

    removeDegree(node->degree);
}

// Helper function to print a single term
void List::printTerm(const Node *node, bool &first, float x) const
{
    float coeff = node->coefficient;
    int deg = node->degree;

    if (coeff == 0.0f)
        return;

    // Handle sign
    if (coeff > 0 && !first)
        std::cout << " + ";
    else if (coeff < 0 && first)
        std::cout << "-";
    else if (coeff < 0)
        std::cout << " - ";

    // Handle coefficient
    if (deg == 0 || std::abs(coeff) != 1.0f)
        std::cout << std::abs(coeff);

    // Handle variable and degree
    if (deg > 0)
    {
        if (std::isnan(x))
            std::cout << "x";
        else
            std::cout << " x (" << x << ")";
        if (deg > 1)
            std::cout << "^" << deg;
    }

    first = false;
}

// Print the polynomial
void List::showALL() const
{
    if (isEmpty())
    {
        std::cout << "0" << std::endl;
        return;
    }

    const Node *node = head;
    bool first = true;
    while (node != nullptr)
    {
        printTerm(node, first);
        node = node->next;
    }
    std::cout << std::endl;
}

// evaluate the polynomial at a given point x
void List::evaluate(float x)
{
    if (isEmpty())
    {
        std::cout << "p(" << x << ") = 0" << std::endl;
        return;
    }

    const Node *node = head;
    float result = 0.0f;

    std::cout << "p(" << x << ") = ";
    bool first = true;

    while (node != nullptr)
    {
        result += node->coefficient * std::pow(x, node->degree);
        printTerm(node, first, x);
        node = node->next;
    }
    std::cout << " = " << result << std::endl;
}

int List::getDegree() const
{
    if (isEmpty())
        return 0;

    return head->degree;
}

Node *List::getHead() const
{
    return head;
}

int List::getNumTerms() const
{
    return size();
}

List List::operator+(const List &other) const
{
    List result(*this); // Start with a copy of the current polynomial

    Node *current = other.head;
    while (current != nullptr)
    {
        result.insert(current->coefficient, current->getDegree());
        current = current->getNext();
    }

    return result;
}

List List::operator-(const List &other) const
{
    List result(*this); // Start with a copy of the current polynomial

    Node *current = other.head;
    while (current != nullptr)
    {
        result.insert(-current->coefficient, current->getDegree());
        current = current->getNext();
    }

    return result;
}

List List::operator*(const List &other) const
{
    List result;

    Node *currentThis = head;
    while (currentThis != nullptr)
    {
        Node *currentOther = other.head;
        while (currentOther != nullptr)
        {
            float coeff = currentThis->coefficient * currentOther->coefficient;
            int deg = currentThis->degree + currentOther->degree;
            result.insert(coeff, deg);
            currentOther = currentOther->next;
        }
        currentThis = currentThis->next;
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const List &list)
{
    if (list.isEmpty())
    {
        os << "0";
        return os;
    }

    Node *node = list.getHead();
    bool first = true;
    while (node != nullptr)
    {
        float coeff = node->getCoefficient();
        int deg = node->getDegree();

        if (coeff == 0.0f)
        {
            node = node->getNext();
            continue;
        }

        // Handle sign
        if (coeff > 0 && !first)
            os << " + ";
        else if (coeff < 0)
            os << " - ";

        // Handle coefficient
        if (deg == 0 || std::abs(coeff) != 1.0f)
            os << std::abs(coeff);

        // Handle variable and degree
        if (deg > 0)
        {
            os << "x";
            if (deg > 1)
                os << "^" << deg;
        }

        first = false;
        node = node->getNext();
    }

    return os;
}