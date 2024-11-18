#include "List.h"
#include <iostream>

int main()
{
    List polynomial;

    // Insert terms
    polynomial.insert(-2.0f, 2);  // +2x^2
    polynomial.insert(3.0f, 4);  // 3x^4
    polynomial.insert(-5.0f, 3); // -5x^3
    polynomial.insert(-2.0f, 0); // -2
    polynomial.insert(1.0f, 1);  // +x

    // Print the polynomial
    std::cout << "Polynomial: ";
    polynomial.print(); // Expected Output: 3x^4 - 5x^3 + 2x^2 + x - 2

    // Change a node's coefficient
    // Update degree 2 coefficient to 4.0f (from 2.0f to 6.0f)
    polynomial.changeNode(4.0f, 2);

    // Print the updated polynomial
    std::cout << "After updating degree 2: ";
    polynomial.print(); // Expected Output: 3x^4 - 5x^3 + 6x^2 + x - 2

    // Remove a node
    // Remove degree 3 term (-5x^3)
    polynomial.removeDegree(3);

    // Print the polynomial after removal
    std::cout << "After removing degree 3: ";
    polynomial.print(); // Expected Output: 3x^4 + 6x^2 + x - 2
    polynomial.showAll();

    return 0;
}
