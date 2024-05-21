#pragma once
#include <miniCAtomsToIntel8080/translator.h>
#include <format>
#include <string>

namespace miniCAtomsToIntel8080
{
    Translator::Translator(miniCSemanticAnalyzer::SymbolTable &symtable, std::unordered_map<std::string, std::vector<std::pair<int, miniCSemanticAnalyzer::Atom>>> &functionMap) : symtable{symtable}, functionMap{functionMap}
    {
        outputASM.open("./output/i8080.asm");
        contextMap = symtable.GetContextMap();
    }

    void Translator::popN(int n)
    {
        for (int i = 0; i < n; i++)
        {
            outputASM << "POP B" << std::endl;
        }
        outputASM << std::endl;
    }

    void Translator::pushN(int n)
    {
        for (int i = 0; i < n; i++)
        {
            outputASM << "PUSH B" << std::endl;
        }
        outputASM << std::endl;
    }

    void Translator::loadOp(const std::string &value)
    {
        if (value.starts_with('\''))
        {
            outputASM << std::format("MVI A, {}", value.substr(1, value.size() - 2)) << std::endl;
            return;
        }

        miniCSemanticAnalyzer::SymbolData &sd = symtable.GetSymbolData(value);

        if (sd.Scope == -1)
        {
            outputASM << std::format("LDA {}", sd.Name) << std::endl;
            return;
        }

        int offsetShift = sd.Offset;

        for (size_t i = contextArray.size() - 1; i > 0; --i)
        {
            if (sd.Scope == contextArray[i])
            {
                break;
            }

            offsetShift += contextMap[contextArray[i]].Len * 2;
        }

        outputASM << std::format("LXI H, {}; load {}", offsetShift, sd.Name) << std::endl
                  << "DAD SP" << std::endl
                  << "MOV A, M" << std::endl
                  << std::endl;
    }

    void Translator::saveOp(const std::string &value)
    {
        miniCSemanticAnalyzer::SymbolData &sd = symtable.GetSymbolData(value);

        if (sd.Scope == -1)
        {
            outputASM << std::format("LDA {}", sd.Name) << std::endl;
            return;
        }

        int offsetShift = sd.Offset;

        for (size_t i = contextArray.size() - 1; i > 0; --i)
        {
            if (sd.Scope == contextArray[i])
            {
                break;
            }

            offsetShift += contextMap[contextArray[i]].Len * 2;
        }

        outputASM << std::format("LXI H, {}; save {}", offsetShift, sd.Name) << std::endl
                  << "DAD SP" << std::endl
                  << "MOV M, A" << std::endl
                  << std::endl;
    }

    void Translator::loader()
    {
        outputASM << "ORG 8000H" << std::endl;

        for (auto code : symtable.GetContextMap()[-1].Vars)
        {
            miniCSemanticAnalyzer::SymbolData &tmpSd = symtable.GetSymbolData(std::to_string(code));
            outputASM << std::format("{}: DB {}", tmpSd.Name, tmpSd.Init) << std::endl;
        }

        outputASM << "ORG 0" << std::endl
                  << std::endl;

        outputASM << "LXI H, 0" << std::endl
                  << "SPHL" << std::endl
                  << "PUSH B" << std::endl
                  << "CALL func_main_0" << std::endl
                  << "END" << std::endl
                  << "@MULT: ..." << std::endl
                  << "@PRINT: ..." << std::endl
                  << std::endl;
    }

    void Translator::OR(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ORA B" << std::endl;
        saveOp(atom.GetThird());
        std::cout << std::endl;
    }

    void Translator::AND(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ANA B" << std::endl;
        saveOp(atom.GetThird());
        std::cout << std::endl;
    }

    void Translator::MOV(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetFirst());
        saveOp(atom.GetThird());
    }

    void Translator::EQ(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::NE(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JNZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::GT(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JP {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LT(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JM {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LE(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JM {}", atom.GetThird()) << std::endl
                  << std::format("JZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LBL(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        outputASM << std::format("{}:", atom.GetThird()) << std::endl;
    }

    void Translator::ADD(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ADD B" << std::endl;
        saveOp(atom.GetThird());
        std::cout << std::endl;
    }

    void Translator::SUB(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "SUB B" << std::endl;
        saveOp(atom.GetThird());
        std::cout << std::endl;
    }

    void Translator::MUL(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        // TODO: Как вызвать Mult?
    }

    void Translator::NOT(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetFirst());
        outputASM << "CMA" << std::endl;
        saveOp(atom.GetThird());
        std::cout << std::endl;
    }

    void Translator::CALL(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        // TODO: Сделать CALL
    }

    void Translator::PARAM(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        programStack.push(atom.GetThird());
    }

    void Translator::RET(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        // TODO: Сделать RET
    }

    void Translator::JMP(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        outputASM << std::format("JMP {}", atom.GetThird()) << std::endl;
    }

    void Translator::IN(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        outputASM << "IN 0" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::OUT(miniCSemanticAnalyzer::Atom &atom, int scope)
    {
        loadOp(atom.GetThird());
        outputASM << "OUT 1" << std::endl;
    }

    void Translator::run()
    {
        loader();

        for (auto &&[funcCode, atoms] : functionMap)
        {
            miniCSemanticAnalyzer::SymbolData &funcSd = symtable.GetSymbolData(funcCode);
            outputASM << std::format("{}:", funcSd.Name) << std::endl;

            contextArray.push_back(atoms.back().first);

            pushN(contextMap[contextArray.back()].Len - std::stoi(funcSd.Len) - 1);

            for (auto &&[scope, atom] : atoms)
            {
                while (scope != contextArray.back())
                {
                    if (contextMap[scope].PrevContext == contextArray.back())
                    {
                        contextArray.push_back(scope);
                        pushN(contextMap[contextArray.back()].Len);
                    }
                    else
                    {
                        popN(contextMap[contextArray.back()].Len);
                        contextArray.pop_back();
                    }
                }

                switch (atom.GetType())
                {
                case miniCSemanticAnalyzer::AtomType::OR:
                    OR(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::AND:
                    AND(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::MOV:
                    MOV(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::EQ:
                    EQ(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::NE:
                    NE(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::GT:
                    GT(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::LT:
                    LT(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::LE:
                    LE(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::LBL:
                    LBL(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::ADD:
                    ADD(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::SUB:
                    SUB(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::MUL:
                    MUL(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::NOT:
                    NOT(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::CALL:
                    CALL(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::PARAM:
                    PARAM(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::RET:
                    RET(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::JMP:
                    JMP(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::IN:
                    IN(atom, scope);
                    break;
                case miniCSemanticAnalyzer::AtomType::OUT:
                    OUT(atom, scope);
                    break;
                }
            }

            contextArray.clear();
            outputASM << std::endl;
        }
    }

    void Translator::Translate()
    {
        run();
    }
}