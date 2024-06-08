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
        NE,
        GT,
        LT,
        LE,
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
        OUT,
        ENTERCTX,
        EXITCTX
    };

    class Atom
    {
    private:
        AtomType type;
        const std::string first;
        const std::string second;
        const std::string third;

    public:
        const std::string GetTypeStr() const;
        const AtomType GetType() const;
        const std::string GetFirst() const;
        const std::string GetSecond() const;
        const std::string GetThird() const;
        Atom(const AtomType type, const std::string first, const std::string second, const std::string third);
        Atom();
    };
    std::ostream &operator<<(std::ostream &os, const Atom &atom);
}
