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
        std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>> functionMap;
        miniCSemanticAnalyzer::SymbolTable symtable;
        std::ofstream outputASM;
        miniCSemanticAnalyzer::SymbolData funcSd;

        std::unordered_map<int, miniCSemanticAnalyzer::Context> contextMap;

        void run();

        void loadOp(const std::string &value, int shift = 0);
        void saveOp(const std::string &value);

        void loader();

        void popN(int n);
        void pushN(int n);

        void OR(miniCSemanticAnalyzer::Atom &atom);
        void AND(miniCSemanticAnalyzer::Atom &atom);
        void MOV(miniCSemanticAnalyzer::Atom &atom);
        void EQ(miniCSemanticAnalyzer::Atom &atom);
        void NE(miniCSemanticAnalyzer::Atom &atom);
        void GT(miniCSemanticAnalyzer::Atom &atom);
        void LT(miniCSemanticAnalyzer::Atom &atom);
        void LE(miniCSemanticAnalyzer::Atom &atom);
        void LBL(miniCSemanticAnalyzer::Atom &atom);
        void ADD(miniCSemanticAnalyzer::Atom &atom);
        void SUB(miniCSemanticAnalyzer::Atom &atom);
        void MUL(miniCSemanticAnalyzer::Atom &atom);
        void NOT(miniCSemanticAnalyzer::Atom &atom);
        void CALL(miniCSemanticAnalyzer::Atom &atom);
        void PARAM(miniCSemanticAnalyzer::Atom &atom);
        void RET(miniCSemanticAnalyzer::Atom &atom);
        void JMP(miniCSemanticAnalyzer::Atom &atom);
        void IN(miniCSemanticAnalyzer::Atom &atom);
        void OUT(miniCSemanticAnalyzer::Atom &atom);

        void ENTERCTX(int scope);
        void EXITCTX();

        public: 
        Translator(miniCSemanticAnalyzer::SymbolTable &symtable, std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>> &functionMap);
        void Translate();
    };
}