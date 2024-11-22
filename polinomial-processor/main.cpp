#include <iostream>
#include "include/FileProcessor.h"

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
