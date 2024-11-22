// FileProcessor.cpp

#include "FileProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>

/**
 * @brief Trims leading and trailing whitespace from a string.
 *
 * This function removes any leading and trailing whitespace characters from the input string.
 *
 * @param str The input string to be trimmed.
 * @return A new string with leading and trailing whitespace removed.
 */
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Reads a file and returns a vector of trimmed, non-empty lines.
 *
 * This function opens the specified file, reads its contents line by line, trims each line,
 * and stores non-empty lines into a vector.
 *
 * @param filename The path to the file to be read.
 * @return A vector containing trimmed, non-empty lines from the file.
 *
 * @throws std::cerr If the file cannot be opened, an error message is printed and the program exits.
 */
std::vector<std::string> trimFileLines(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << "Erro: Não foi possível abrir o arquivo '" << filename << "' para leitura." << std::endl;
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

/**
 * @brief Extracts the command character from a line.
 *
 * This function parses a line to determine if it represents a valid command.
 * If the line contains exactly one character, it converts it to lowercase and assigns it to the command.
 * Otherwise, it sets the command to a null character indicating an invalid command.
 *
 * @param line The input line from which to extract the command.
 * @param command Pointer to a character where the extracted command will be stored.
 */
void getCommand(const std::string &line, char *command)
{
    if (line.length() == 1)
    {
        *command = std::tolower(line[0]);
    }
    else
    {
        *command = '\0'; // Comando inválido
    }
}

/**
 * @brief Populates a polynomial from a line containing coefficient and degree pairs.
 *
 * This function parses a line containing pairs of coefficients and degrees,
 * and inserts each term into the provided polynomial list.
 *
 * @param line The input line containing coefficient and degree pairs.
 * @param poly Reference to a `List` object representing the polynomial to be populated.
 *
 * @throws std::cerr If the input line is empty, an error message is printed and the program exits.
 */
void populatePolynomial(const std::string &line, List &poly)
{
    if (line.empty())
    {
        std::cerr << "Erro: Linha de polinômio inválida." << std::endl;
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

/**
 * @brief Processes a single command with the given polynomials and optional evaluation point.
 *
 * This function executes the specified command by performing operations on the provided polynomials.
 * Supported commands include addition ('+'), subtraction ('-'), multiplication ('*'), getting the degree ('g'),
 * printing the polynomial ('p'), evaluating the polynomial ('a'), and getting the number of terms ('t').
 *
 * @param command The command character indicating the operation to perform.
 * @param poly1 Reference to the first `List` object representing the first polynomial.
 * @param poly2 Reference to the second `List` object representing the second polynomial.
 * @param x Optional float value used for evaluating the polynomial when the command is 'a'.
 */
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
                poly1.evaluate(x); // Removed assignment since evaluate returns void
            }
            else
            {
                std::cerr << "Erro: Valor de x inválido para avaliação." << std::endl;
            }
            poly1 = List();
            break;
        }
        case 't':
        {
            std::cout << "Número de termos do polinômio: ";
            poly1.showALL(false);
            std::cout << " , é " << poly1.size() << std::endl;
            poly1 = List();
            break;
        }
        default:
            std::cout << "Erro: Comando inválido." << std::endl;
    }
}

/**
 * @brief Processes the entire file by reading commands and executing them.
 *
 * This function reads a file containing commands and polynomial data, processes each line,
 * and performs the corresponding operations on the polynomials.
 *
 * The file is expected to contain commands followed by the necessary polynomial data or evaluation points.
 *
 * @param filePath The path to the input file to be processed.
 */
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
            std::cerr << "Erro: Comando inválido na linha " << count + 1 << ": " << line << std::endl;
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
                    std::cerr << "Erro: Linhas insuficientes para a operação '" << command << "' iniciando na linha " << count + 1 << std::endl;
                    return;
                }
                populatePolynomial(lines[++count], poly1);
                populatePolynomial(lines[++count], poly2);
                processLine(command, poly1, poly2); // Passing NaN as default
                break;
            }
            case 'p':
            case 'g':
            case 't':
            {
                if (count + 1 >= lines.size())
                {
                    std::cerr << "Erro: Linhas insuficientes para o comando '" << command << "' iniciando na linha " << count + 1 << std::endl;
                    return;
                }
                populatePolynomial(lines[++count], poly1);
                processLine(command, poly1, poly2); // Passing NaN as default
                break;
            }
            case 'a':
            {
                if (count + 2 >= lines.size())
                {
                    std::cerr << "Erro: Linhas insuficientes para o comando 'a' iniciando na linha " << count + 1 << std::endl;
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
                std::cout << "Erro: Comando inválido na linha " << count + 1 << ": " << line << std::endl;
        }
        count++;
    }
}
