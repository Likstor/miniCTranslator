#pragma once
#include <miniCLexer/lexer.h>
#include <string>
#include <unordered_map>

struct Operator
{
    unsigned int priority;
    std::string associative;
};

class ShuntingYardMachine
{
private:
    miniCLexer::Lexer &lexer;

    std::unordered_map<std::string, Operator> operators{
        {"lpar", {3, "LEFT"}},
        {"rpar", {3, "LEFT"}},
        {"opplus", {1, "LEFT"}},
        {"opminus", {1, "LEFT"}},
        {"opmul", {2, "LEFT"}},
    };

public:
    ShuntingYardMachine(miniCLexer::Lexer &lexer);
    std::vector<miniCLexer::Token> getReversePolishNotation();
};
