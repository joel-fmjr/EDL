#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include <vector>
#include "List.h"

// Trims leading and trailing whitespace from a string
std::string trim(const std::string &str);

// Reads a file and returns a vector of trimmed, non-empty lines
std::vector<std::string> trimFileLines(const std::string &filename);

// Extracts the command character from a line
void getCommand(const std::string &line, char *command);

// Populates a polynomial from a line containing coefficient and degree pairs
void populatePolynomial(const std::string &line, List &poly);

// Processes a single command with the given polynomials and optional evaluation point
void processLine(char command, List &poly1, List &poly2, float x = NAN);

// Processes the entire file by reading commands and executing them
void processFile(const std::string &filePath);

#endif // FILEPROCESSOR_H
