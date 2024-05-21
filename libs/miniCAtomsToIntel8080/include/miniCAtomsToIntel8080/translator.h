#pragma once
#include <miniCSemanticAnalyzer/symtable.h>
#include <miniCSemanticAnalyzer/atom.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stack>

namespace miniCAtomsToIntel8080
{
    class Translator
    {
    private:
        std::stack<std::string> programStack;
        std::vector<int> contextArray;
        std::unordered_map<std::string, std::vector<std::pair<int, miniCSemanticAnalyzer::Atom>>> functionMap;
        miniCSemanticAnalyzer::SymbolTable symtable;
        std::ofstream outputASM;

        int currentMaxOffset;
        int currentScope;
        std::unordered_map<int, miniCSemanticAnalyzer::Context> contextMap;

        void run();

        void loadOp(const std::string &value);
        void saveOp(const std::string &value);

        void loader();

        void popN(int n);
        void pushN(int n);

        void OR(miniCSemanticAnalyzer::Atom &atom, int scope);
        void AND(miniCSemanticAnalyzer::Atom &atom, int scope);
        void MOV(miniCSemanticAnalyzer::Atom &atom, int scope);
        void EQ(miniCSemanticAnalyzer::Atom &atom, int scope);
        void NE(miniCSemanticAnalyzer::Atom &atom, int scope);
        void GT(miniCSemanticAnalyzer::Atom &atom, int scope);
        void LT(miniCSemanticAnalyzer::Atom &atom, int scope);
        void LE(miniCSemanticAnalyzer::Atom &atom, int scope);
        void LBL(miniCSemanticAnalyzer::Atom &atom, int scope);
        void ADD(miniCSemanticAnalyzer::Atom &atom, int scope);
        void SUB(miniCSemanticAnalyzer::Atom &atom, int scope);
        void MUL(miniCSemanticAnalyzer::Atom &atom, int scope);
        void NOT(miniCSemanticAnalyzer::Atom &atom, int scope);
        void CALL(miniCSemanticAnalyzer::Atom &atom, int scope);
        void PARAM(miniCSemanticAnalyzer::Atom &atom, int scope);
        void RET(miniCSemanticAnalyzer::Atom &atom, int scope);
        void JMP(miniCSemanticAnalyzer::Atom &atom, int scope);
        void IN(miniCSemanticAnalyzer::Atom &atom, int scope);
        void OUT(miniCSemanticAnalyzer::Atom &atom, int scope);

    public:
        Translator(miniCSemanticAnalyzer::SymbolTable &symtable, std::unordered_map<std::string, std::vector<std::pair<int, miniCSemanticAnalyzer::Atom>>> &functionMap);
        void Translate();
    };
}