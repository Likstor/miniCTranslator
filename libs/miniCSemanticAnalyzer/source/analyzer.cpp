#pragma once
#include <miniCSemanticAnalyzer/analyzer.h>
#include <miniCBuilderAST/node.h>
#include <iostream>
#include <miniCSemanticAnalyzer/atom.h>

namespace miniCSemanticAnalyzer
{
    void SemanticAnalyzer::E(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E"}, true);

        treePrint.push_back(0);
        E7(Node.GetChildren()[0], treePrint);
    }

    void SemanticAnalyzer::E7(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E7"}, true);

        treePrint.push_back(1);
        E6(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        E7List(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::E7List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E7'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opor")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opor"}, false);

            E6(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            E7List(Node.GetChildren()[2], treePrint);
        }
    }

    void SemanticAnalyzer::E6(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E6"}, true);

        treePrint.push_back(1);
        E5(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        E6List(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::E6List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E6'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opand")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opand"}, false);

            E5(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            E6List(Node.GetChildren()[2], treePrint);
        }
    }

    void SemanticAnalyzer::E5(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E5"}, true);

        treePrint.push_back(1);
        E4(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        E5List(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::E5List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E5'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opeq")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opeq"}, false);

            E4(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opne")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opne"}, false);

            E4(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "oplt")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"oplt"}, false);

            E4(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opgt")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opgt"}, false);

            E4(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "ople")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"ople"}, false);

            E4(Node.GetChildren()[1], treePrint);
        }
    }

    void SemanticAnalyzer::E4(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E4"}, true);

        treePrint.push_back(1);
        E3(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        E4List(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::E4List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E4'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opplus")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opplus"}, false);

            E3(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            E4List(Node.GetChildren()[2], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opminus")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opminus"}, false);

            E3(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            E4List(Node.GetChildren()[2], treePrint);
        }
    }

    void SemanticAnalyzer::E3(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E3"}, true);

        treePrint.push_back(1);
        E2(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        E3List(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::E3List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E3'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opmul")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opmul"}, false);

            E2(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            E3List(Node.GetChildren()[2], treePrint);
        }
    }

    void SemanticAnalyzer::E2(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E2"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "opnot")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opnot"}, false);

            E1(Node.GetChildren()[1], treePrint);
        }
        else
        {
            treePrint.push_back(0);
            E1(Node.GetChildren()[0], treePrint);
        }
    }

    void SemanticAnalyzer::E1(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E1"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "id")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, false);

            E1List(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "num")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);

            E(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opinc", Node.GetChildren()[1].GetValues()[0]}, true);
        }
    }

    void SemanticAnalyzer::E1List(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E1'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetLexemeType()}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);

            ArgList(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
    }

    void SemanticAnalyzer::ArgList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ArgList"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        E(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(1);
        ArgListList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::ArgListList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ArgList'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma"}, false);

        E(Node.GetChildren()[1], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        ArgListList(Node.GetChildren()[2], treePrint);
    }

    void SemanticAnalyzer::DeclareStmt(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"DeclareStmt"}, true);

        treePrint.push_back(1);
        Type(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[1].GetValues()[0]}, false);

        DeclareStmtList(Node.GetChildren()[2], treePrint);
    }

    void SemanticAnalyzer::DeclareStmtList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"DeclareStmtList"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);

            ParamList(Node.GetChildren()[1], treePrint);

            printTreeString(treePrint, {"rpar", "lbrace"}, false);

            StmtList(Node.GetChildren()[4], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rbrace"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opassign")
        {
            if (Node.GetChildren()[1].GetLexemeType() == "num")
            {
                treePrint.push_back(0);
                printTreeString(treePrint, {"opassign", Node.GetChildren()[1].GetValues()[0]}, false);

                DeclVarListList(Node.GetChildren()[2], treePrint);
            }
            else if (Node.GetChildren()[1].GetLexemeType() == "chr")
            {
                treePrint.push_back(0);
                printTreeString(treePrint, {"opassign", Node.GetChildren()[1].GetValues()[0]}, false);

                DeclVarListList(Node.GetChildren()[2], treePrint);
            }
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "DeclVarList'")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opassign", Node.GetChildren()[1].GetValues()[0]}, false);
            DeclVarListList(Node.GetChildren()[0], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"semicolon"}, true);
        }
    }

    void SemanticAnalyzer::Type(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Type"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "kwchar")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"kwchar"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "kwint")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"kwint"}, true);
        }
    }

    void SemanticAnalyzer::DeclVarListList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"DeclVarList'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma", Node.GetChildren()[1].GetValues()[0]}, false);
        InitVar(Node.GetChildren()[2], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        DeclVarListList(Node.GetChildren()[3], treePrint);
    }

    void SemanticAnalyzer::InitVar(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"InitVar"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(0);
        printTreeString(treePrint, {"opassign"}, false);
        InitVarList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::InitVarList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"InitVar'"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "num")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "chr")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
        }
    }

    void SemanticAnalyzer::ParamList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ParamList"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        Type(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[1].GetValues()[0]}, false);
        ParamListList(Node.GetChildren()[2], treePrint);
    }

    void SemanticAnalyzer::ParamListList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ParamList'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma"}, false);
        Type(Node.GetChildren()[1], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[2].GetValues()[0]}, false);

        ParamListList(Node.GetChildren()[3], treePrint);
    }

    void SemanticAnalyzer::StmtList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"StmtList"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        Stmt(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        StmtList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::Stmt(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Stmt"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "DeclareStmt")
        {
            treePrint.push_back(0);
            DeclareStmt(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "AssignOrCallOp")
        {
            treePrint.push_back(0);
            AssignOrCallOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "WhileOp")
        {
            treePrint.push_back(0);
            WhileOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "ForOp")
        {
            treePrint.push_back(0);
            ForOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "IfOp")
        {
            treePrint.push_back(0);
            IfOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "SwitchOp")
        {
            treePrint.push_back(0);
            SwitchOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "IOp")
        {
            treePrint.push_back(0);
            IOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "OOp")
        {
            treePrint.push_back(0);
            OOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lbrace")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"lbrace"}, false);

            StmtList(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rbrace"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "kwreturn")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"kwreturn"}, false);

            E(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"semicolon"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "semicolon")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"semicolon"}, true);
        }
    }

    void SemanticAnalyzer::AssignOrCallOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCallOp"}, true);

        treePrint.push_back(1);
        AssignOrCall(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"semicolon"}, true);
    }

    void SemanticAnalyzer::AssignOrCall(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCall"}, true);

        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, false);

        AssignOrCallList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::AssignOrCallList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCall'"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "opassign")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opassign"}, false);
            E(Node.GetChildren()[1], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"ArgList"}, false);
            ArgList(Node.GetChildren()[1], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
    }

    void SemanticAnalyzer::WhileOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCall'"}, true);

        treePrint.push_back(1);

        printTreeString(treePrint, {"kwwhile", "lpar"}, false);
        E(Node.GetChildren()[2], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rpar"}, false);

        Stmt(Node.GetChildren()[4], treePrint);
    }

    void SemanticAnalyzer::ForOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwfor", "lpar"}, false);

        ForInit(Node.GetChildren()[2], treePrint);

        printTreeString(treePrint, {"semicolon"}, false);
        ForExp(Node.GetChildren()[4], treePrint);

        printTreeString(treePrint, {"semicolon"}, false);
        ForLoop(Node.GetChildren()[6], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rpar"}, false);
        Stmt(Node.GetChildren()[8], treePrint);
    }
    void SemanticAnalyzer::ForInit(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForInit"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(0);
        AssignOrCall(Node.GetChildren()[0], treePrint);
    }

    void SemanticAnalyzer::ForExp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForExp"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(0);
        E(Node.GetChildren()[0], treePrint);
    }
    void SemanticAnalyzer::ForLoop(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForExp"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opinc", Node.GetChildren()[1].GetValues()[0]}, true);
        }
        else
        {
            treePrint.push_back(0);
            AssignOrCall(Node.GetChildren()[0], treePrint);
        }
    }

    void SemanticAnalyzer::IfOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"IfOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwif", "lpar"}, false);

        E(Node.GetChildren()[2], treePrint);

        printTreeString(treePrint, {"rpar"}, false);

        Stmt(Node.GetChildren()[4], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        ElsePart(Node.GetChildren()[5], treePrint);
    }

    void SemanticAnalyzer::ElsePart(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ElsePart"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(0);
        printTreeString(treePrint, {"kwelse"}, false);

        Stmt(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::SwitchOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"SwitchOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwswitch", "lpar"}, false);

        E(Node.GetChildren()[2], treePrint);

        printTreeString(treePrint, {"rpar", "lbrace"}, false);

        Cases(Node.GetChildren()[5], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rbrace"}, true);
    }

    void SemanticAnalyzer::Cases(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Cases"}, true);

        treePrint.push_back(1);
        ACase(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        CasesList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::CasesList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Cases'"}, true);

        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        treePrint.push_back(1);
        ACase(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        CasesList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::ACase(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Cases'"}, true);

        treePrint.push_back(0);
        if (Node.GetChildren()[0].GetLexemeType() == "kwcase")
        {
            printTreeString(treePrint, {"kwcase", Node.GetChildren()[1].GetValues()[0], "colon"}, false);
            StmtList(Node.GetChildren()[3], treePrint);
        }
        else
        {
            printTreeString(treePrint, {"kwdefault", "colon"}, false);
            StmtList(Node.GetChildren()[2], treePrint);
        }
    }

    void SemanticAnalyzer::IOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"IOp'"}, true);

        treePrint.push_back(0);
        printTreeString(treePrint, {"kwin", Node.GetChildren()[1].GetValues()[0], "semicolon"}, true);
    }

    void SemanticAnalyzer::OOp(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"OOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwout"}, false);
        OOpList(Node.GetChildren()[1], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"semicolon"}, true);
    }
    void SemanticAnalyzer::OOpList(miniCBuilderAST::Node& Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"OOp'"}, true);

        treePrint.push_back(0);
        if (Node.GetChildren()[0].GetLexemeType() == "E")
        {
            E(Node.GetChildren()[0], treePrint);
        }
        else
        {
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
        }
    }

    void SemanticAnalyzer::printTreeString(std::vector<int> treePrint, std::vector<std::string> nodes, bool newString)
    {
        std::string subTree = "├";
        std::string lineTree = "│";
        std::string finTree = "└";

        if (prevNewString)
        {
            for (size_t i = 0; i < treePrint.size(); i++)
            {
                if (treePrint[i] == 0)
                {
                    if (i + 1 == treePrint.size())
                    {
                        outputFile << finTree;
                        continue;
                    }

                    outputFile << ' ';
                }
                else
                {
                    if (i + 1 == treePrint.size())
                    {
                        outputFile << subTree;
                        continue;
                    }

                    outputFile << lineTree;
                }
            }
        }

        for (std::string node : nodes)
        {
            outputFile << node << " ";
        }

        if (newString)
        {
            prevNewString = true;
            outputFile << std::endl;
        }
        else
        {
            prevNewString = false;
        }
    }

    SemanticAnalyzer::SemanticAnalyzer(miniCBuilderAST::Node& AST) : AST{AST}
    {
        outputFile.open("./outputTree.txt");
    }

    SemanticAnalyzer::~SemanticAnalyzer()
    {
        outputFile.close();
    }

    void SemanticAnalyzer::StartAnalysis()
    {
        StmtList(AST, {});
    }
}