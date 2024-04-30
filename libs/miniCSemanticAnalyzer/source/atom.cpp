#pragma once
#include <miniCSemanticAnalyzer/atom.h>
#include <format>

namespace miniCSemanticAnalyzer
{
    Atom::Atom(const int type, const std::string first, const std::string second, const std::string third) : type{type},
                                                                                                             first{first},
                                                                                                             second{second},
                                                                                                             third{third} {}

    const std::string Atom::GetType() const
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
        case AtomType::NE:
            output = "NE";
            break;
        case AtomType::GT:
            output = "GT";
            break;
        case AtomType::LT:
            output = "LT";
            break;
        case AtomType::LE:
            output = "LE";
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

    const std::string Atom::GetFirst() const
    {
        return first;
    }

    const std::string Atom::GetSecond() const
    {
        return second;
    }
    const std::string Atom::GetThird() const
    {
        return third;
    }

    std::ostream &operator<<(std::ostream &os, const Atom &atom)
    {
        os << "<" << atom.GetType() << ", " << atom.GetFirst() << ", " << atom.GetSecond() << ", " << atom.GetThird() << ">" << std::endl;
        return os;
    }
}