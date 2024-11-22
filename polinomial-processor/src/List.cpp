#include "../include/List.h"
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
#include <sstream>

/**
 * @class List
 * @brief Represents a polynomial as a singly linked list.
 *
 * The List class manages a polynomial where each node contains a coefficient and degree.
 * The list is maintained in descending order of degrees to facilitate polynomial operations
 * such as addition, subtraction, and multiplication.
 */

/**
 * @brief Default constructor that initializes an empty polynomial list.
 *
 * Initializes the head and tail pointers to nullptr and sets the list size to zero.
 */
List::List()
    : head(nullptr), tail(nullptr), listSize(0) {}

/**
 * @brief Copy constructor that creates a deep copy of another List.
 *
 * @param other The List object to copy from.
 *
 * Initializes the new list by copying nodes from the `other` list.
 */
List::List(const List &other)
    : head(nullptr), tail(nullptr), listSize(0)
{
    copyFrom(other);
}

/**
 * @brief Destructor that cleans up all dynamically allocated nodes in the list.
 *
 * Calls the `clear` method to delete all nodes and reset pointers.
 */
List::~List()
{
    clear();
}

/**
 * @brief Copy assignment operator that assigns one List to another.
 *
 * @param other The List object to assign from.
 * @return Reference to the assigned List object.
 *
 * Performs a deep copy of the `other` list into the current list.
 * Handles self-assignment by checking if the current object is the same as `other`.
 */
List &List::operator=(const List &other)
{
    if (this == &other)
        return *this;

    clear();
    copyFrom(other);
    return *this;
}

/**
 * @brief Inserts a term into the list in sorted order.
 *
 * @param coefficient The coefficient of the term to insert.
 * @param degree The degree of the term to insert.
 *
 * If a term with the same degree already exists, its coefficient is updated.
 * The list maintains descending order based on degrees.
 *
 * @note Degrees must be non-negative integers. Terms with a zero coefficient are not inserted.
 */
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

/**
 * @brief Removes a node with a specific degree from the list.
 *
 * @param degree The degree of the term to remove.
 *
 * Searches for the node with the given degree and removes it from the list.
 * Updates the head and tail pointers as necessary.
 */
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

/**
 * @brief Checks whether a term with a specific degree exists in the list.
 *
 * @param degree The degree to search for.
 * @return `true` if a term with the given degree exists; otherwise, `false`.
 */
bool List::exists(int degree) const
{
    return search(degree) != nullptr;
}

/**
 * @brief Retrieves the number of terms in the polynomial.
 *
 * @return The total number of terms (nodes) in the list.
 */
int List::size() const
{
    return listSize;
}

/**
 * @brief Checks whether the polynomial list is empty.
 *
 * @return `true` if the list is empty; otherwise, `false`.
 */
bool List::isEmpty() const
{
    return head == nullptr;
}

/**
 * @brief Searches for a node by its degree.
 *
 * @param degree The degree of the term to search for.
 * @return Pointer to the node with the specified degree if found; otherwise, `nullptr`.
 */
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

/**
 * @brief Retrieves the head node of the list.
 *
 * @return Pointer to the head node.
 */
Node *List::getHead() const
{
    return head;
}

/**
 * @brief Retrieves the next node after a given node.
 *
 * @param node Pointer to the current node.
 * @return Pointer to the next node if it exists; otherwise, `nullptr`.
 */
Node *List::getNext(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    return node->next;
}

/**
 * @brief Retrieves the coefficient and degree of a term by its degree.
 *
 * @param degree The degree of the term to retrieve.
 * @return A tuple containing the coefficient and degree. Returns {0.0f, 0} if not found.
 */
std::tuple<float, int> List::getValues(int degree) const
{
    Node *node = search(degree);
    if (node == nullptr)
        return {0.0f, 0};
    return {node->coefficient, node->degree};
}

/**
 * @brief Retrieves the highest degree of the polynomial.
 *
 * @return The degree of the first term (highest degree) if the list is not empty; otherwise, `0`.
 */
int List::getDegree() const
{
    if (isEmpty())
        return 0;

    return head->degree;
}

/**
 * @brief Evaluates the polynomial for a given value of x.
 *
 * @param x The value at which to evaluate the polynomial.
 *
 * Calculates the result by summing each term's coefficient multiplied by x raised to the term's degree.
 * Outputs the evaluation process and result to the console.
 *
 * @note If the list is empty, the result is `0`.
 */
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

/**
 * @brief Prints the polynomial to the console.
 *
 * @param endl If `true`, appends a newline character after printing; otherwise, no newline.
 *
 * Utilizes the `toString` method to generate a string representation of the polynomial.
 * If the list is empty, prints `0`.
 */
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

/**
 * @brief Generates a string representation of the polynomial.
 *
 * @param x Optional parameter used for formatting when evaluating the polynomial. Defaults to NaN.
 * @return A string representing the polynomial.
 *
 * Constructs the polynomial string by iterating through the list and formatting each term.
 * Handles positive and negative coefficients, as well as degrees for superscript representation.
 */
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

/**
 * @brief Formats a floating-point number to a string with appropriate precision.
 *
 * @param number The number to format.
 * @return A string representation of the number with up to two decimal places if necessary.
 *
 * If the number is an integer, it is converted without decimal places.
 * Otherwise, it is formatted with two decimal places.
 */
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

/**
 * @brief Converts an integer to its superscript string representation.
 *
 * @param number The integer to convert.
 * @return A string containing the superscript characters of the number.
 *
 * Maps each digit to its corresponding Unicode superscript character.
 * Example: 12 becomes "¹²".
 */
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

/**
 * @brief Changes the coefficient and degree of a node with a specific current degree.
 *
 * @param currentDegree The current degree of the term to change.
 * @param coefficient The new coefficient to set.
 * @param degree The new degree to set.
 *
 * If a node with `currentDegree` exists, its coefficient is updated. If the new coefficient is zero,
 * the node is removed. If the node does not exist, a new term is inserted.
 */
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

/**
 * @brief Overloads the addition operator to add two polynomials.
 *
 * @param other The List object to add to the current polynomial.
 * @return A new List object representing the sum of the two polynomials.
 *
 * Creates a copy of the current polynomial, inserts all terms from `other`, and returns the result.
 */
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

/**
 * @brief Overloads the subtraction operator to subtract one polynomial from another.
 *
 * @param other The List object to subtract from the current polynomial.
 * @return A new List object representing the difference between the two polynomials.
 *
 * Creates a copy of the current polynomial, inserts all negated terms from `other`, and returns the result.
 */
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

/**
 * @brief Overloads the multiplication operator to multiply two polynomials.
 *
 * @param other The List object to multiply with the current polynomial.
 * @return A new List object representing the product of the two polynomials.
 *
 * Performs a nested iteration over both polynomials, multiplying each term from the current polynomial
 * with each term from `other`, and inserts the resulting terms into the result polynomial.
 */
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

/**
 * @brief Overloads the insertion operator to allow easy printing of the polynomial.
 *
 * @param os The output stream.
 * @param list The List object representing the polynomial to print.
 * @return Reference to the output stream with the polynomial appended.
 *
 * Utilizes the `toString` method to convert the polynomial to a string and inserts it into the stream.
 */
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

/**
 * @brief Helper method to delete all nodes in the list.
 *
 * Iterates through the list, deletes each node, and resets the head, tail, and list size.
 */
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

/**
 * @brief Helper method to perform a deep copy of another List.
 *
 * @param other The List object to copy from.
 *
 * Copies all nodes from the `other` list into the current list, maintaining the order of terms.
 */
void List::copyFrom(const List &other)
{
    if (other.isEmpty())
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