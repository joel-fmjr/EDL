#include <iostream>
#include <tuple>

using namespace std;

class Node
{
    private:
        float coefficient;
        int degree;
        Node *next;

    public:
        Node(float coefficient, int degree)
        {

            this->coefficient = coefficient;
            this->degree = degree;
            this->next = nullptr;
        }
    
        friend class List;
};

class List
{

    public:
        Node* head = nullptr;
        Node* tail = nullptr;

        List()
        {
            head = tail = nullptr;
        }

        ~List()
        {
            Node *current = head;
            while (current != nullptr)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
        }

        Node *getNext(Node *node)
        {
            return node->next;
        }

        tuple<float, int> getValues(Node *node)
        {
            return make_tuple(node->coefficient, node->degree);
        }

        void changeNode(Node *node, float coefficient, int degree)
        {
            if (node->degree != degree)
            {
                deleteNode(node);
                insert(coefficient, degree);
                return;
            }
            node->coefficient = coefficient;
        }

        int size()
        {
            int count = 0;
            Node *current = head;
            while (current->next != nullptr)
            {
                count++;
                current = current->next;
            }
            return count;
        }

        bool isEmpty()
        {
            return head == nullptr;
        }

        bool exists(Node *node)
        {
            Node *current = head;
            while (current != nullptr)
            {
                if (current == node)
                {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        void insert(float coefficient, int degree)
        {
            sortedInsertByDegree(coefficient, degree);
        }

        void remove(Node *node)
        {
            if (isEmpty())
            {
                return;
            }
            if (head == node)
            {
                head = head->next;
                return;
            }
            Node *current = head;
            while (current->next != nullptr)
            {
                if (current->next == node)
                {
                    current->next = node->next;
                    return;
                }
                current = current->next;
            }
        }

        void deleteNode(Node *node)
        {
            if (isEmpty())
            {
                return;
            }
            if (head == node)
            {
                head = head->next;
                delete node;
                return;
            }
            Node *current = head;
            while (current->next != nullptr)
            {
                if (current->next == node)
                {
                    current->next = node->next;
                    delete node;
                    return;
                }
                current = current->next;
            }
        }

        Node *searchDegree(int degree)
        {
            Node *current = head;
            while (current != nullptr)
            {
                if (current->degree == degree)
                {
                    return current;
                }
                current = current->next;
            }
            return nullptr;
        }

        void p()
        {
            Node *node = head;
            while (node != nullptr)
            {
                if (node->degree == 0)
                {
                    std::cout << node->coefficient << " ";
                }
                else if (node->degree == 1)
                {
                    std::cout << node->coefficient << "x ";
                }
                else
                {
                    std::cout << node->coefficient << "x^" << node->degree << " ";
                }
                node = node->next;
            }
        };
    
    private:

        bool updateCoefficientOnExistingDegree(float coefficient, int degree)
        {
            Node *existingDegree = searchDegree(degree);
            if (existingDegree != nullptr)
            {
                existingDegree->coefficient += coefficient;
                return true;
            }
            return false;
        }
        void sortedInsertByDegree(float coefficient, int degree)
        {
            if (updateCoefficientOnExistingDegree(coefficient, degree))
            {
                return;
            }

            Node *newNode = new Node(coefficient, degree);
            if (isEmpty())
            {
                head = tail = newNode;
            }
            else if (head->degree <= degree)
            {
                newNode->next = head;
                head = newNode;
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
            }
        }
};

int main()
{
    List list;
    list.insert(3, 2);
    list.insert(4, 1);
    list.insert(2, 3);
    list.insert(5, 0);

    list.p();
    cout << endl;

    float coefficient;
    int degree;
    Node *node = list.getNext(list.head);
    tie(coefficient, degree) = list.getValues(node);
    cout << coefficient << " " << degree << endl;
    list.changeNode(node, 10, 2);
    list.insert(5.2, 2);
    list.p();

    return 0;
}
