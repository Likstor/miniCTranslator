#pragma once
#include <string>
#include <iostream>

namespace miniCSemanticAnalyzer
{
    enum AtomType
    {
        ERROR,
        OR,
        AND,
        MOV,
        EQ,
        LBL,
        ADD,
        SUB,
        MUL,
        NOT,
        CALL,
        PARAM,
        RET,
        JMP,
        IN,
        OUT
    };

    class Atom
    {
    private:
        int type;
        std::string first;
        std::string second;
        std::string third;

    public:
        std::string GetType();
        std::string GetFirst();
        std::string GetSecond();
        std::string GetThird();
        Atom(int type, std::string first, std::string second, std::string third);
    };

    std::ostream &operator<<(std::ostream &os, const Atom &atom);
}
