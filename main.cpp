#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <miniCLexer/lexer.h>

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "None file path";
        return -1;
    }

    std::ifstream stream(argv[1], std::ios::in);

    miniCLexer::Lexer lexer{stream};

    while (true)
    {
        miniCLexer::Token temp = lexer.getNextLexem();

        std::cout << "[" << temp.token << ", \"" << temp.value << "\"]" << std::endl;

        if (temp.token == "error" || temp.token == "eof")
        {
            break;
        }
    }
}
