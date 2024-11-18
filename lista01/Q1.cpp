#include <iostream>
#include <tuple>

class List; // Forward declaration

class Node
{
private:
    float coefficient;
    int degree;
    Node* next;

public:
    Node(float coeff, int deg)
        : coefficient(coeff), degree(deg), next(nullptr) {}

    // Getters
    float getCoefficient() const { return coefficient; }
    int getDegree() const { return degree; }
    Node* getNext() const { return next; }

    friend class List;
};

class List
{
private:
    Node* head;
    Node* tail;
    int listSize;

    // Helper method to deep copy nodes
    void copyFrom(const List& other)
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
    void clear()
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

public:
    // Constructor
    List()
        : head(nullptr), tail(nullptr), listSize(0) {}

    // Copy Constructor
    List(const List& other)
        : head(nullptr), tail(nullptr), listSize(0)
    {
        copyFrom(other);
    }

    // Copy Assignment Operator
    List& operator=(const List& other)
    {
        if (this == &other)
            return *this;

        clear();
        copyFrom(other);
        return *this;
    }

    // Destructor
    ~List()
    {
        clear();
    }

    // Get the next node
    Node* getNext(const Node* node) const
    {
        if (node == nullptr)
            return nullptr;
        return node->next;
    }

    // Get the coefficient and degree as a tuple
    std::tuple<float, int> getValues(const Node* node) const
    {
        if (node == nullptr)
            return {0.0f, 0};
        return {node->coefficient, node->degree};
    }

    // Change node's coefficient and degree
    void changeNode(Node* node, float coefficient, int degree)
    {
        if (node == nullptr)
            return;

        if (node->degree != degree)
        {
            // Remove the node and re-insert with new degree
            remove(node);
            insert(coefficient, degree);
        }
        else
        {
            node->coefficient = coefficient;
            if (node->coefficient == 0.0f)
            {
                remove(node);
            }
        }
    }

    // Get the size of the list
    int size() const
    {
        return listSize;
    }

    // Check if the list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Check if a node exists in the list
    bool exists(const Node* node) const
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current == node)
                return true;
            current = current->next;
        }
        return false;
    }

    // Insert a term into the list in sorted order
    void insert(float coefficient, int degree)
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
                remove(existingNode);
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

    // Remove a node from the list
    void remove(Node* node)
    {
        if (node == nullptr || isEmpty())
            return;

        if (head == node)
        {
            head = head->next;
            delete node;
            if (head == nullptr)
                tail = nullptr;
            listSize--;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next != node)
        {
            current = current->next;
        }

        if (current->next == node)
        {
            current->next = node->next;
            if (node == tail)
                tail = current;
            delete node;
            listSize--;
        }
    }

    // Delete a node from the list (same as remove)
    void deleteNode(Node* node)
    {
        remove(node);
    }

    // Search for a node by degree
    Node* searchDegree(int degree) const
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

    // Print the polynomial
    void print() const
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
};


int main()
{
    List polynomial;

    // Insert terms
    polynomial.insert(3.0f, 4);  // 3x^4
    polynomial.insert(2.0f, 2);  // +2x^2
    polynomial.insert(-5.0f, 3); // -5x^3
    polynomial.insert(1.0f, 1);  // +x
    polynomial.insert(-2.0f, 0); // -2

    // Print the polynomial
    polynomial.print(); // Expected Output: 3x^4 - 5x^3 + 2x^2 + x - 2

    // Change a node's coefficient
    Node* node = polynomial.searchDegree(2);
    if (node)
    {
        polynomial.changeNode(node, 4.0f, 2); // Update 2x^2 to 4x^2
    }

    // Print the updated polynomial
    polynomial.print(); // Expected Output: 3x^4 - 5x^3 + 4x^2 + x - 2

    float coefficient;
    int degree;

    // Remove a node
    node = polynomial.searchDegree(3);
    if (node)
    {
        
        std::tie(coefficient, degree) = polynomial.getValues(node);
        std::cout << "Removing " << coefficient << "x^" << degree << std::endl;
        polynomial.remove(node);
    }

    // Print the polynomial after removal
    polynomial.print(); // Expected Output: 3x^4 + 4x^2 + x - 2
    node = polynomial.searchDegree(4);
    std::tie(coefficient, degree) = polynomial.getValues(node);
    std::cout << node->getCoefficient() << "x^" << node->getCoefficient() << std::endl;
    polynomial.insert(1.0f, 4); // Insert a zero coefficient term
    std::cout << node->getCoefficient() << "x^" << node->getCoefficient() << std::endl;
    polynomial.print(); // Expected Output: 4x^2 + x - 2

    return 0;
}