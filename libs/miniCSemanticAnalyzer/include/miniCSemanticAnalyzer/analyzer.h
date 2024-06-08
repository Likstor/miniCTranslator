#pragma once
#include <miniCBuilderAST/node.h>
#include <fstream>
#include <miniCSemanticAnalyzer/symtable.h>
#include <miniCSemanticAnalyzer/atom.h>

namespace miniCSemanticAnalyzer
{
    class SemanticAnalyzer
    {
    private:
        std::ofstream outputTree;
        std::ofstream outputAtoms;
        std::ofstream outputTable;

        miniCBuilderAST::Node AST;
        miniCSemanticAnalyzer::SymbolTable symtable;

        std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>> functionMap;
        std::string currentFunction;
        bool mainCheck = false;

        bool prevNewString = true;

        void E(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E7(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E7List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E6(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E6List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E5(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E5List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E4(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E4List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E3(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E3List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E2(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E1(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void E1List(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void ArgList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ArgListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void DeclareStmt(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void DeclareStmtList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void Type(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void DeclVarListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void InitVar(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void InitVarList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void ParamList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ParamListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void StmtList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void Stmt(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void AssignOrCallOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void AssignOrCall(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void AssignOrCallList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void WhileOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void ForOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ForInit(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ForExp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ForLoop(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void IfOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ElsePart(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void SwitchOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void Cases(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void CasesList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void ACase(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void IOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void OOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint);
        void OOpList(miniCBuilderAST::Node &Node, std::vector<int> treePrint);

        void printTreeString(std::vector<int> treePrint, std::vector<std::string> nodes, bool newString);

        void recordAtom(miniCSemanticAnalyzer::Atom &atom);

    public:
        SemanticAnalyzer(miniCBuilderAST::Node &AST);
        void StartAnalysis();
        ~SemanticAnalyzer();
        miniCSemanticAnalyzer::SymbolTable& GetSymTable();
        std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>>& GetFunctionMap();
    };
}