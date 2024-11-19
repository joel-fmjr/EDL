#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "List.h"

void processLine(char command, List poly1, List poly2)
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
    else if (command == 'g' || command == 'G')
    { // Grau do polinômio
        std::cout << "Grau do polinômio 1: " << poly1.getDegree() << std::endl;
    }
    else if (command == 'p' || command == 'P')
    { // Exibir polinômio
        std::cout << "Polinômio 1: ";
        poly1.showALL();
        poly1 = List();
    }
    // else if (command == 'a' || command == 'A')
    // { // Avaliar polinômio
    //     float x;
    //     iss >> x;
    //     if (firstPoly)
    //     {
    //         std::cout << "Resultado de p(" << x << ") para o polinômio 1: ";
    //         poly1.evaluate(x);
    //     }
    //     else
    //     {
    //         std::cout << "Resultado de p(" << x << ") para o polinômio 2: ";
    //         poly2.evaluate(x);
    //     }
    // }
}

void populatePolynomial(const std::string &line, List &poly)
{
    std::istringstream iss(line);
    float coefficient;
    int degree;
    while (iss >> coefficient >> degree)
    {
        poly.insert(coefficient, degree);
    }
    poly.showALL();
}

void getCommand(const std::string &line, char *command, char *previousCommand)
{

    if (line.length() > 1){
        *command = 'i';
        return;
    }

    std::istringstream iss(line);
    if (*command != '0')
    {
        *previousCommand = *command;
    }
    *command = line[0];
    std::cout << "Command: " << *command << std::endl;

    if (*command != '+' && *command != 'g' && *command != 'e' && *command != 'a')
    {
        *command = 'i';
    }
}

void processFile(const std::string &filePath)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
        return;
    }

    std::string line;
    List poly1, poly2, result;
    char previousCommand = '0';
    char command = '0';

    while (std::getline(inputFile, line))
    {

        if (line.empty())
        {
            continue;
        }
        getCommand(line, &command, &previousCommand);
        // std::cout << "Command: " << command << std::endl;
        if (command == 'i')
        {
            // std::cout << "entrou no if" << std::endl;
            poly1.isEmpty() ? populatePolynomial(line, poly1) : populatePolynomial(line, poly2);
        }

        // if (!poly1.isEmpty() && !poly2.isEmpty())
        // {
        //     result = poly1 + poly2;
        //     result.showALL();
        // }

        processLine(command, poly1, poly2);
    }

    inputFile.close();
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
