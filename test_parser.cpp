#include <iostream>

#include "parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string file_name = "";
    std::cout << "Enter file name with JSON information: ";
    std::cin >> file_name;

    parser p(file_name);
    p.parse();
    p.print();

    return 0;
}