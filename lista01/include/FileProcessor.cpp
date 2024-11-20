// FileProcessor.cpp
#include "FileProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>

// Trims leading and trailing whitespace from a string
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// Reads a file and returns a vector of trimmed, non-empty lines
std::vector<std::string> trimFileLines(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << "Error: Unable to open file '" << filename << "' for reading." << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line))
    {
        line = trim(line);
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }
    inputFile.close();
    return lines;
}

// Extracts the command character from a line
void getCommand(const std::string &line, char *command)
{
    if (line.length() == 1)
    {
        *command = std::tolower(line[0]);
    }
    else
    {
        // Handle invalid command length
        *command = '\0';
    }
}

// Populates a polynomial from a line containing coefficient and degree pairs
void populatePolynomial(const std::string &line, List &poly)
{
    if (line.empty())
    {
        std::cerr << "Polinômio inválido." << std::endl;
        exit(1);
    }

    std::istringstream iss(line);
    float coefficient;
    int degree;
    while (iss >> coefficient >> degree)
    {
        poly.insert(coefficient, degree);
    }
}

// Processes a single command with the given polynomials and optional evaluation point
void processLine(char command, List &poly1, List &poly2, float x)
{
    switch (command)
    {
        case '+':
        {
            List result = poly1 + poly2;
            std::cout << "Resultado da soma dos polinômios: ";
            result.showALL();
            poly1 = List();
            poly2 = List();
            break;
        }
        case '-':
        {
            List result = poly1 - poly2;
            std::cout << "Resultado da subtração dos polinômios: ";
            result.showALL();
            poly1 = List();
            poly2 = List();
            break;
        }
        case '*':
        {
            List result = poly1 * poly2;
            std::cout << "Resultado da multiplicação dos polinômios: ";
            result.showALL();
            poly1 = List();
            poly2 = List();
            break;
        }
        case 'g':
        {
            std::cout << "O grau do polinômio: ";
            poly1.showALL(false);
            std::cout << " , é " << poly1.getDegree() << std::endl;
            poly1 = List();
            break;
        }
        case 'p':
        {
            std::cout << "Polinômio: ";
            poly1.showALL();
            poly1 = List();
            break;
        }
        case 'a':
        {
            if (!std::isnan(x))
            {
                poly1.evaluate(x);
            }
            else
            {
                std::cerr << "Valor de x inválido para avaliação." << std::endl;
            }
            poly1 = List();
            break;
        }
        case 't':
        {
            std::cout << "Número de termos do polinômio: ";
            poly1.showALL(false);
            std::cout << " , é " << poly1.getNumTerms() << std::endl;
            poly1 = List();
            break;
        }
        default:
            std::cout << "Comando inválido" << std::endl;
    }
}

// Processes the entire file by reading commands and executing them
void processFile(const std::string &filePath)
{
    std::vector<std::string> lines = trimFileLines(filePath);
    List poly1, poly2;
    char command = '\0';
    size_t count = 0;

    while (count < lines.size())
    {
        std::string line = lines[count];
        getCommand(line, &command);

        if (command == '\0')
        {
            std::cerr << "Comando inválido na linha " << count + 1 << ": " << line << std::endl;
            count++;
            continue;
        }

        switch (command)
        {
            case '+':
            case '-':
            case '*':
            {
                if (count + 2 >= lines.size())
                {
                    std::cerr << "Insufficient lines for operation '" << command << "' starting at line " << count + 1 << std::endl;
                    return;
                }
                populatePolynomial(lines[++count], poly1);
                populatePolynomial(lines[++count], poly2);
                processLine(command, poly1, poly2);
                break;
            }
            case 'p':
            case 'g':
            case 't':
            {
                if (count + 1 >= lines.size())
                {
                    std::cerr << "Insufficient lines for command '" << command << "' starting at line " << count + 1 << std::endl;
                    return;
                }
                populatePolynomial(lines[++count], poly1);
                processLine(command, poly1, poly2);
                break;
            }
            case 'a':
            {
                if (count + 2 >= lines.size())
                {
                    std::cerr << "Insufficient lines for command 'a' starting at line " << count + 1 << std::endl;
                    return;
                }
                float x;
                try
                {
                    x = std::stof(lines[++count]);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Erro ao converter valor de x na linha " << count + 1 << std::endl;
                    return;
                }
                populatePolynomial(lines[++count], poly1);
                processLine(command, poly1, poly2, x);
                break;
            }
            default:
                std::cout << "Comando inválido na linha " << count + 1 << ": " << line << std::endl;
        }
        count++;
    }
}
