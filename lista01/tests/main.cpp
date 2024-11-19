#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "List.h"

void processLine(char command, List &poly1, List &poly2, float x = NAN)
{
    // std::cout << "Command: " << command << std::endl;
    if (command == '+')
    { // Soma dos dois polinômios
        List result = poly1 + poly2;
        std::cout << "Resultado da soma dos polinômios: ";
        result.showALL();
        poly1 = List();
        poly2 = List();
    }
    else if (command == '-')
    { // Grau do polinômio
        List result = poly1 - poly2;
        std::cout << "Resultado da subtração dos polinômios: ";
        result.showALL();
        poly1 = List();
    }
    else if (command == '*')
    { // Multiplicação dos dois polinômios
        List result = poly1 * poly2;
        std::cout << "Resultado da multiplicação dos polinômios: ";
        result.showALL();
        poly1 = List();
        poly2 = List();
    }
    else if (command == 'g' || command == 'G')
    { // Grau do polinômio
        std::cout << "Grau do polinômio: " << poly1.getDegree() << std::endl;
        poly1 = List();
    }
    else if (command == 'p' || command == 'P')
    { // Exibir polinômio
        poly1.showALL();
        poly1 = List();
    }
    else if (command == 'a' || command == 'A')
    { // Avaliar polinômio
        poly1.evaluate(x);
        poly1 = List();
    }
    else
    {
        std::cout << "Comando inválido" << std::endl;
    }
}

void populatePolynomial(const std::string &line, List &poly)
{
    if (line.length() <= 1) {
        std::cout << "Invalid polynomial" << std::endl;
        exit(1);
    }
    std::istringstream iss(line);
    float coefficient;
    int degree;
    while (iss >> coefficient >> degree)
    {
        poly.insert(coefficient, degree);
    }
    // poly.showALL();
}

void getCommand(const std::string &line, char *command)
{
    if (line.length() > 1)
    {
        return;
    }

    *command = line[0];
}

// Trim function as defined earlier
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> trimFileLines(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file '" << filename << "' for reading." << std::endl;
        exit(1);
    }

    // Read all lines into a vector
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        line = trim(line);
        if (line.empty()) {
            continue;
        }
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}

void processFile(const std::string &filePath)
{
    std::vector<std::string> lines = trimFileLines(filePath);

    std::string line;
    List poly1, poly2;
    char command = '0';
    size_t count = 0;

    while (count < lines.size())
    {
        line = lines[count];

        if (line.empty())
        {
            continue;
        }

        getCommand(line, &command);

        if (command == '+' || command == '-' || command == '*')
        {

            populatePolynomial(lines[++count], poly1);
            populatePolynomial(lines[++count], poly2);
            processLine(command, poly1, poly2);
        }
        else if (command == 'p' || command == 'P')
        {
            populatePolynomial(lines[++count], poly1);
            processLine(command, poly1, poly2);            
        }
        else if (command == 'g' || command == 'G')
        {
            populatePolynomial(lines[++count], poly1);
            processLine(command, poly1, poly2);
        }
        else if (command == 'a' || command == 'A')
        {
            float x = std::stof(lines[++count]);
            populatePolynomial(lines[++count], poly1);
            processLine(command, poly1, poly2, x);
        }
        else
        {
            std::cout << "Comando inválido" << std::endl;
        }
        count++;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_o_arquivo>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    processFile(filePath);

    return 0;
}
