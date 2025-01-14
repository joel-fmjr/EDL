#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>

int CheckBalancedExpression(std::string expression)
{
    std::stack<char> stack;
    std::unordered_map<char, char> map = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char character : expression)
    {
        if (character == '(' || character == '[' || character == '{')
        {
            stack.push(character);
        }
        else if (character == ')' || character == ']' || character == '}')
        {
            if (stack.empty() || stack.top() != map[character])
            {
                return 0;
            }
            stack.pop();
        }
    }

    return stack.empty();
}

int main()
{
    std::string expressions[7] = {
        "(a + b)",
        "{[a * (b + c)]}",
        "a + {b - [c * d]}",
        "a + (b",
        "{[a * b]",
        "(a + b)}",
        "a + {b - [c * d}"};

    for (std::string exp : expressions)
    {
        std::cout << CheckBalancedExpression(exp) << std::endl;
    }
    return 0;
}