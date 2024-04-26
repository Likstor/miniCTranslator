#pragma once
#include <miniCSemanticAnalyzer/atom.h>
#include <format>

namespace miniCSemanticAnalyzer
{
    Atom::Atom(int type, std::string first, std::string second, std::string third) : type{type},
                                                                                    first{first},
                                                                                    second{second},
                                                                                    third{third} {}

    std::string Atom::GetType()
    {
        std::string output;

        switch (type)
        {
        case 0:
            output = "ERROR";
            break;
        case AtomType::OR:
            output = "OR";
            break;
        case AtomType::AND:
            output = "AND";
            break;
        case AtomType::MOV:
            output = "MOV";
            break;
        case AtomType::EQ:
            output = "EQ";
            break;
        case AtomType::LBL:
            output = "LBL";
            break;
        case AtomType::ADD:
            output = "ADD";
            break;
        case AtomType::SUB:
            output = "SUB";
            break;
        case AtomType::MUL:
            output = "MUL";
            break;
        case AtomType::NOT:
            output = "NOT";
            break;
        case AtomType::CALL:
            output = "CALL";
            break;
        case AtomType::PARAM:
            output = "PARAM";
            break;
        case AtomType::RET:
            output = "RET";
            break;
        case AtomType::JMP:
            output = "JMP";
            break;
        case AtomType::IN:
            output = "IN";
            break;
        case AtomType::OUT:
            output = "OUT";
            break;
        default:
            output = "UNKNOWN";
        }

        return output;
    }

    std::string Atom::GetFirst()
    {
        return first;
    }

    std::string Atom::GetSecond()
    {
        return second;
    }
    std::string Atom::GetThird()
    {
        return third;
    }

    std::ostream &operator<<(std::ostream &os, Atom &atom)
    {
        return os << std::format("<%d, %d, %d, %d>", atom.GetType(), atom.GetFirst(), atom.GetSecond(), atom.GetThird());
    }
}