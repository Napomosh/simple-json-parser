#include <iostream>

#include "parser.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Incorrect input" << std::endl;
        return 1;
    }
    else if (argc > 2) {
        std::cout << "Only the first file will be parse" << std::endl;
    }
    setlocale(LC_ALL, "Russian");

    std::string file_name = argv[1];
    std::cout << "Your file for parsing" << file_name << std::endl << std::endl;

    parser p(file_name);
    p.parse();
    p.print();

    return 0;
}