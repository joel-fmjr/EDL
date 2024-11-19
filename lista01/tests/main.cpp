#include "List.h"
#include <iostream>

int main()
{
    List polynomial;

    // Insert terms
    polynomial.insert(-5.0f, 1); // -5x
    polynomial.insert(3.0f, 2);  // +3x^2
    polynomial.insert(7.0f, 0);  // +7

    List otherPolynomial;

    // Insert terms
    otherPolynomial.insert(-4.0f, 0); // -4
    otherPolynomial.insert(2.0f, 2);  // +2x^2
    otherPolynomial.insert(6.0f, 1);  // +6x

    // Print the polynomial
    polynomial.showALL(); // Expected Output: 3x^2 - 5x + 7

    // Print the other polynomial
    otherPolynomial.showALL(); // Expected Output: 2x^2 + 6x - 4

    // Get the size of the polynomial
    std::cout << "Size of the polynomial: " << polynomial.getNumTerms() << std::endl; // Expected Output: 4

    // Get the degree of the polynomial
    std::cout << "Degree of the polynomial: " << polynomial.getDegree() << std::endl; // Expected Output: 4

    // sum of polynomials
    List sum = polynomial + otherPolynomial;
    sum.showALL(); // Expected Output: 5x^2 +x + 3

    // difference of polynomials
    List sub = polynomial - otherPolynomial;
    sub.showALL(); // Expected Output: x^2 - 11x + 11

    // product of polynomials
    List prod = polynomial * otherPolynomial;
    prod.showALL(); // Expected Output: 6x^4 + 8x^3 - 28x^2 + 62x - 28

    List evaluation;
    evaluation.insert(-2.0f, 2);
    evaluation.insert(4.0f, 1);

    // evaluate the polynomial
    evaluation.evaluate(3.0f); // Expected Output: -6

    List polynomial2;
    polynomial2.insert(2.0f, 2);
    polynomial2.insert(-4.0f, 1);
    polynomial2.insert(1.0f, 0);

    List polynomial3;
    polynomial3.insert(-3.0f, 4);
    polynomial3.insert(5.0f, 2);
    polynomial3.insert(4.0f, 1);
    polynomial3.insert(-10.0f, 0);

    // sum of polynomials
    List sum2 = polynomial2 + polynomial3;
    sum2.showALL(); // Expected Output: -3x^4 + 7x^2 - 3x - 9

    return 0;
}
