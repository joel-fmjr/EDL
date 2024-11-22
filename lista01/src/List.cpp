#include "List.h"
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
#include <sstream>

// Constructor
List::List()
    : head(nullptr), tail(nullptr), listSize(0) {}

// Copy Constructor
List::List(const List &other)
    : head(nullptr), tail(nullptr), listSize(0)
{
    copyFrom(other);
}

// Destructor
List::~List()
{
    clear();
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

// Insert a term into the list in sorted order
void List::insert(float coefficient, int degree)
{
    if (coefficient == 0.0f)
        return;

    if (degree < 0)
    {
        std::cerr << "O grau deve ser um número inteiro não negativo.\n";
        return;
    }

    // Check if degree already exists and update coefficient if it does
    Node *existingNode = search(degree);
    if (existingNode != nullptr)
    {
        existingNode->coefficient += coefficient;
        if (existingNode->coefficient == 0.0f)
        {
            remove(degree);
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
void List::remove(int degree)
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

bool List::exists(int degree) const
{
    return search(degree) != nullptr;
}

int List::size() const
{
    return listSize;
}

bool List::isEmpty() const
{
    return head == nullptr;
}

// Search for a node by degree
Node *List::search(int degree) const
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

Node *List::getHead() const
{
    return head;
}

Node *List::getNext(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    return node->next;
}

std::tuple<float, int> List::getValues(int degree) const
{
    Node *node = search(degree);
    if (node == nullptr)
        return {0.0f, 0};
    return {node->coefficient, node->degree};
}

int List::getDegree() const
{
    if (isEmpty())
        return 0;

    return head->degree;
}

void List::evaluate(float x)
{
    if (isEmpty())
    {
        std::cout << "p(" << x << ") = 0" << std::endl;
        return;
    }

    float result = 0.0f;

    Node *current = head;
    while (current != nullptr)
    {
        result += current->coefficient * std::pow(x, current->degree);
        current = current->next;
    }

    std::cout << "p(" << x << ") = ";

    std::cout << toString(x);
    std::cout << " = " << result << std::endl;
}

// Print the polynomial
void List::showALL(bool endl) const
{
    if (isEmpty())
    {
        std::cout << "0" << std::endl;
        return;
    }

    std::cout << toString();

    if (endl)
    {
        std::cout << std::endl;
    }
}

std::string List::toString(float x) const
{
    if (!head)
        return "0";

    Node *current = head;
    std::string result;
    bool first = true;

    while (current)
    {
        float coeff = current->coefficient;
        int deg = current->degree;

        if (coeff > 0 && !first)
            result += " + ";
        else if (coeff < 0 && first)
            result += "-";
        else if (coeff < 0)
            result += " - ";

        if (deg == 0 || std::abs(coeff) != 1.0f)
            result += formatPrecision(std::abs(coeff));

        if (deg > 0)
        {
            if (std::isnan(x))
                result += "x";
            else if (coeff != 1.0f && coeff != -1.0f)
                result += " x (" + formatPrecision(x) + ")";
            else
                result += "(" + formatPrecision(x) + ")";
            if (deg > 1)
                result += toSuperscript(deg);
        }

        first = false;
        current = current->next;
    }

    return result;
}

std::string List::formatPrecision(float number) const
{
    std::stringstream stream;
    if (std::floor(number) == number)
    {
        return std::to_string((int)number);
    }
    else
    {
        stream << std::fixed << std::setprecision(2) << number;
        std::string s = stream.str();
        return s;
    }
    return std::to_string(number);
}

// Function to convert a number to its superscript string
std::string List::toSuperscript(int number) const
{
    std::map<char, std::string> superscripts = {
        {'0', "\u2070"},
        {'1', "\u00B9"},
        {'2', "\u00B2"},
        {'3', "\u00B3"},
        {'4', "\u2074"},
        {'5', "\u2075"},
        {'6', "\u2076"},
        {'7', "\u2077"},
        {'8', "\u2078"},
        {'9', "\u2079"},
    };

    // convert number to string
    std::string numberStr = std::to_string(number);

    std::string result = "";
    for (char digit : numberStr)
    {
        result += superscripts[digit];
    }

    return result;
}

// Change the coefficient and degree of a node with a specific degree
void List::changeNode(int currentDegree, float coefficient, int degree)
{
    Node *node = search(currentDegree);
    if (node == nullptr)
    {
        std::cerr << "Grau " << currentDegree << " não encontrado. Inserindo novo termo.\n";
        insert(coefficient, degree);
        return;
    }

    node->coefficient = coefficient;

    if (node->coefficient == 0.0f)
    {
        remove(degree);
    }
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

    os << list.toString();

    return os;
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