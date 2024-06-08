#pragma once
#include <miniCSemanticAnalyzer/analyzer.h>
#include <miniCBuilderAST/node.h>
#include <iostream>
#include <miniCSemanticAnalyzer/atom.h>
#include <miniCSemanticAnalyzer/exception.h>
#include <format>

namespace miniCSemanticAnalyzer
{
    void SemanticAnalyzer::E(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e7 = Node.GetChildren()[0];

        printTreeString(treePrint, {"E"}, true);

        treePrint.push_back(0);
        E7(e7, treePrint);

        Node.NewVal(e7.GetValues()[0]); // p = q
    }

    void SemanticAnalyzer::E7(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e6 = Node.GetChildren()[0];
        miniCBuilderAST::Node &e7l = Node.GetChildren()[1];

        printTreeString(treePrint, {"E7"}, true);

        treePrint.push_back(1);
        E6(e6, treePrint);

        e7l.NewVal(e6.GetValues()[0]); // r = q

        treePrint.pop_back();
        treePrint.push_back(0);
        E7List(e7l, treePrint);
        Node.NewVal(e7l.GetValues()[1]); // p = s
    }

    void SemanticAnalyzer::E7List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E7'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal(Node.GetValues()[0]); // q = p
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opor")
        {
            miniCBuilderAST::Node &e6 = Node.GetChildren()[1];
            miniCBuilderAST::Node &e7l = Node.GetChildren()[2];

            treePrint.push_back(1);
            printTreeString(treePrint, {"opor"}, false);

            E6(e6, treePrint);

            std::string s = symtable.Alloc(); // s = alloc(C)

            Atom OR{AtomType::OR, Node.GetValues()[0], e6.GetValues()[0], s};
            recordAtom(OR);

            e7l.NewVal(s);

            treePrint.pop_back();
            treePrint.push_back(0);
            E7List(e7l, treePrint);

            Node.NewVal(e7l.GetValues()[1]);
        }
    }

    void SemanticAnalyzer::E6(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e5 = Node.GetChildren()[0];
        miniCBuilderAST::Node &e6l = Node.GetChildren()[1];

        printTreeString(treePrint, {"E6"}, true);

        treePrint.push_back(1);
        E5(e5, treePrint);

        e6l.NewVal(e5.GetValues()[0]); // r = q;

        treePrint.pop_back();
        treePrint.push_back(0);
        E6List(e6l, treePrint);

        Node.NewVal(e6l.GetValues()[1]); // p = s
    }

    void SemanticAnalyzer::E6List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E6'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal(Node.GetValues()[0]); // q = p
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opand")
        {
            miniCBuilderAST::Node &e5 = Node.GetChildren()[1];
            miniCBuilderAST::Node &e6l = Node.GetChildren()[2];

            treePrint.push_back(1);
            printTreeString(treePrint, {"opand"}, false);

            E5(e5, treePrint);
            std::string s = symtable.Alloc(); // s = alloc(C)

            Atom AND{AtomType::AND, Node.GetValues()[0], e5.GetValues()[0], s};
            recordAtom(AND);

            e6l.NewVal(s);

            treePrint.pop_back();
            treePrint.push_back(0);
            E6List(e6l, treePrint);

            Node.NewVal(e6l.GetValues()[1]); // q = t
        }
    }

    void SemanticAnalyzer::E5(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e4 = Node.GetChildren()[0];
        miniCBuilderAST::Node &e5l = Node.GetChildren()[1];

        printTreeString(treePrint, {"E5"}, true);

        treePrint.push_back(1);
        E4(e4, treePrint);

        e5l.NewVal(e4.GetValues()[0]); // r = q

        treePrint.pop_back();
        treePrint.push_back(0);
        E5List(e5l, treePrint);

        Node.NewVal(e5l.GetValues()[1]); // p = s
    }

    void SemanticAnalyzer::E5List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E5'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal(Node.GetValues()[0]); // q = p
            return;
        }

        miniCBuilderAST::Node &e4 = Node.GetChildren()[1];

        std::string s = symtable.Alloc();    // s = alloc(C)
        std::string l = symtable.NewLabel(); // l = newLabel()

        Atom MOV_1{AtomType::MOV, "'1'", "", s};
        recordAtom(MOV_1);

        if (Node.GetChildren()[0].GetLexemeType() == "opeq")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opeq"}, false);

            E4(e4, treePrint);

            Atom EQ{AtomType::EQ, Node.GetValues()[0], e4.GetValues()[0], l};
            recordAtom(EQ);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opne")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opne"}, false);

            E4(e4, treePrint);

            Atom NE{AtomType::NE, Node.GetValues()[0], e4.GetValues()[0], l};
            recordAtom(NE);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "oplt")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"oplt"}, false);

            E4(e4, treePrint);

            Atom LT{AtomType::LT, Node.GetValues()[0], e4.GetValues()[0], l};
            recordAtom(LT);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opgt")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opgt"}, false);

            E4(e4, treePrint);

            Atom GT{AtomType::GT, Node.GetValues()[0], e4.GetValues()[0], l};
            recordAtom(GT);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "ople")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"ople"}, false);

            E4(e4, treePrint);

            Atom LE{AtomType::LE, Node.GetValues()[0], e4.GetValues()[0], l};
            recordAtom(LE);
        }

        Atom MOV_2{AtomType::MOV, "'0'", "", s};
        recordAtom(MOV_2);

        Atom LBL{AtomType::LBL, "", "", l};
        recordAtom(LBL);

        Node.NewVal(s); // q = s
    }

    void SemanticAnalyzer::E4(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e3 = Node.GetChildren()[0];
        miniCBuilderAST::Node &e4l = Node.GetChildren()[1];

        printTreeString(treePrint, {"E4"}, true);

        treePrint.push_back(1);
        E3(e3, treePrint);

        e4l.NewVal(e3.GetValues()[0]); // r = q

        treePrint.pop_back();
        treePrint.push_back(0);
        E4List(e4l, treePrint);

        Node.NewVal(e4l.GetValues()[1]); // p = s
    }

    void SemanticAnalyzer::E4List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E4'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal(Node.GetValues()[0]); // q = p
            return;
        }

        miniCBuilderAST::Node &e3 = Node.GetChildren()[1];
        miniCBuilderAST::Node &e4l = Node.GetChildren()[2];

        std::string s;

        if (Node.GetChildren()[0].GetLexemeType() == "opplus")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opplus"}, false);

            E3(e3, treePrint);

            s = symtable.Alloc(); // s = alloc(C)

            Atom ADD{AtomType::ADD, Node.GetValues()[0], e3.GetValues()[0], s};
            recordAtom(ADD);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opminus")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opminus"}, false);

            E3(e3, treePrint);

            s = symtable.Alloc(); // s = alloc(C)

            Atom SUB{AtomType::SUB, Node.GetValues()[0], e3.GetValues()[0], s};
            recordAtom(SUB);
        }

        e4l.NewVal(s);

        treePrint.pop_back();
        treePrint.push_back(0);
        E4List(e4l, treePrint);

        Node.NewVal(e4l.GetValues()[1]); // q = t
    }

    void SemanticAnalyzer::E3(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e2 = Node.GetChildren()[0];
        miniCBuilderAST::Node &e3l = Node.GetChildren()[1];

        printTreeString(treePrint, {"E3"}, true);

        treePrint.push_back(1);
        E2(e2, treePrint);

        e3l.NewVal(e2.GetValues()[0]); // r = q

        treePrint.pop_back();
        treePrint.push_back(0);
        E3List(e3l, treePrint);

        Node.NewVal(e3l.GetValues()[1]); // p = s
    }

    void SemanticAnalyzer::E3List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E3'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal(Node.GetValues()[0]); // q = p
            return;
        }

        miniCBuilderAST::Node &e2 = Node.GetChildren()[1];
        miniCBuilderAST::Node &e3l = Node.GetChildren()[2];

        std::string s;

        if (Node.GetChildren()[0].GetLexemeType() == "opmul")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"opmul"}, false);

            E2(e2, treePrint);

            s = symtable.Alloc(); // s = alloc(C)

            Atom MUL{AtomType::MUL, Node.GetValues()[0], e2.GetValues()[0], s};
            recordAtom(MUL);

            e3l.NewVal(s);

            treePrint.pop_back();
            treePrint.push_back(0);
            E3List(e3l, treePrint);
        }

        Node.NewVal(e3l.GetValues()[1]); // q = t
    }

    void SemanticAnalyzer::E2(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E2"}, true);

        miniCBuilderAST::Node &e1 = Node.GetChildren().back();

        if (Node.GetChildren()[0].GetLexemeType() == "opnot")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opnot"}, false);

            E1(e1, treePrint);

            std::string r = symtable.Alloc(); // r = alloc(C)

            Atom NOT{AtomType::NOT, e1.GetValues()[0], "", r};
            recordAtom(NOT);
        }
        else
        {
            treePrint.push_back(0);
            E1(e1, treePrint);
        }

        Node.NewVal(e1.GetValues()[0]);
    }

    void SemanticAnalyzer::E1(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E1"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "id")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, false);

            Node.GetChildren()[1].NewVal(Node.GetChildren()[0].GetValues()[0]);

            E1List(Node.GetChildren()[1], treePrint);

            Node.NewVal(Node.GetChildren()[1].GetValues()[1]);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "num")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
            Node.NewVal(std::format("'{}'", Node.GetChildren()[0].GetValues()[0]));
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "chr")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);
            Node.NewVal(std::format("'{}'", std::to_string(int(Node.GetChildren()[0].GetValues()[0][0]))));
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);

            E(Node.GetChildren()[1], treePrint);

            Node.NewVal(Node.GetChildren()[1].GetValues()[0]);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opinc", Node.GetChildren()[1].GetValues()[0]}, true);

            std::string code = symtable.CheckVar(Node.GetChildren()[1].GetValues()[0]);

            Atom ADD{AtomType::ADD, code, "'1'", code};
            recordAtom(ADD);

            Node.NewVal(code);
        }
    }

    void SemanticAnalyzer::E1List(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"E1'"}, true);

        if (Node.IsLeaf())
        {
            std::string s = symtable.CheckVar(Node.GetValues()[0]);
            Node.NewVal(s);
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetLexemeType()}, true);

            std::string s = symtable.CheckVar(Node.GetValues()[0]);
            std::string r = symtable.Alloc();

            Atom MOV{AtomType::MOV, s, "", r};
            Atom ADD{AtomType::ADD, s, "'1'", s};
            recordAtom(MOV);
            recordAtom(ADD);

            Node.NewVal(r);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            std::string &name = Node.GetValues()[0];

            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);

            ArgList(Node.GetChildren()[1], treePrint);

            if (name == "main")
            {
                throw SemanticError("Trying to call main function");
            }

            std::string s = symtable.CheckFunc(name, Node.GetChildren()[1].GetValues()[0]);
            std::string r = symtable.Alloc();

            Atom CALL{AtomType::CALL, s, "", r};
            recordAtom(CALL);

            Node.NewVal(r);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
    }

    void SemanticAnalyzer::ArgList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ArgList"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal("0");
            return;
        }

        miniCBuilderAST::Node &e = Node.GetChildren()[0];
        miniCBuilderAST::Node &argList = Node.GetChildren()[1];

        treePrint.push_back(1);
        E(e, treePrint);

        treePrint.pop_back();
        treePrint.push_back(1);

        Atom PARAM{AtomType::PARAM, "", "", e.GetValues()[0]};
        recordAtom(PARAM);

        ArgListList(argList, treePrint);

        Node.NewVal(std::to_string(std::stoi(argList.GetValues()[0]) + 1));
    }

    void SemanticAnalyzer::ArgListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ArgList'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal("0");
            return;
        }

        miniCBuilderAST::Node &e = Node.GetChildren()[1];
        miniCBuilderAST::Node &argList = Node.GetChildren()[2];

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma"}, false);

        E(e, treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);

        Atom PARAM{AtomType::PARAM, "", "", e.GetValues()[0]};
        recordAtom(PARAM);

        ArgListList(argList, treePrint);

        Node.NewVal(std::to_string(std::stoi(argList.GetValues()[0]) + 1));
    }

    void SemanticAnalyzer::DeclareStmt(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &type = Node.GetChildren()[0];
        miniCBuilderAST::Node &id = Node.GetChildren()[1];
        miniCBuilderAST::Node &dsl = Node.GetChildren()[2];

        printTreeString(treePrint, {"DeclareStmt"}, true);

        treePrint.push_back(1);
        Type(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[1].GetValues()[0]}, false);

        dsl.NewVal(type.GetValues()[0]);
        dsl.NewVal(id.GetValues()[0]);

        DeclareStmtList(Node.GetChildren()[2], treePrint);
    }

    void SemanticAnalyzer::DeclareStmtList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"DeclareStmtList"}, true);
        std::string code;

        if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            if (symtable.GetContext() != -1) // Checking a nested function declaration
            {
                throw SemanticError("Definition function inside another function");
            }

            symtable.EnterContext();

            treePrint.push_back(1);
            printTreeString(treePrint, {"lpar"}, false);
            symtable.AddVarToContext(-2);

            ParamList(Node.GetChildren()[1], treePrint);

            std::string funcCode;
            std::string &name = Node.GetValues()[1];
            std::string type = Node.GetValues()[0];
            // addFunc(q, p)
            if (type == "Char")
            {
                currentFunction = symtable.AddFunc(name, SymbolType::Char, Node.GetChildren()[1].GetValues()[0]);
            }
            else if (type == "Int")
            {
                currentFunction = symtable.AddFunc(name, SymbolType::Int, Node.GetChildren()[1].GetValues()[0]);
            }
            

            symtable.AddVarToContext(-2);

            if (name == "main")
            {
                if (mainCheck)
                {
                    throw SemanticError("An attempt to override the main function");\
                }

                if (Node.GetChildren()[1].GetValues()[0] != "0")
                {
                    throw SemanticError("The main function should have no parameters.");
                }
                mainCheck = true;
            }

            printTreeString(treePrint, {"rpar", "lbrace"}, false);

            Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
            recordAtom(ENTERCTX);

            StmtList(Node.GetChildren()[4], treePrint);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rbrace"}, true);

            Atom RET{AtomType::RET, "", "", "'0'"};
            recordAtom(RET);

            Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
            recordAtom(EXITCTX);
            symtable.ExitContext();
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opassign")
        {
            std::string &value = Node.GetChildren()[1].GetValues()[0];
            std::string &type = Node.GetValues()[0];

            if (Node.GetChildren()[1].GetLexemeType() == "num")
            {
                if (type != "Int" && type != "Char") // Type check
                {
                    throw SemanticError(std::format("{} is of the wrong type", value));
                }

                treePrint.push_back(1);
                printTreeString(treePrint, {"opassign", value}, false);

                SymbolType symtype = type == "Char" ? SymbolType::Char : SymbolType::Int;
                code = symtable.AddVar(Node.GetValues()[1], symtype, value); // addVar(q, C, p, val)

                Atom MOV{AtomType::MOV, std::format("'{}'", value), "", code};
                recordAtom(MOV);

                Node.GetChildren()[2]
                    .NewVal(type); // r = p

                DeclVarListList(Node.GetChildren()[2], treePrint);

                treePrint.pop_back();
                treePrint.push_back(0);
                printTreeString(treePrint, {"semicolon"}, true);
            }
            else if (Node.GetChildren()[1].GetLexemeType() == "chr")
            {
                if (type != "Int" && type != "Char") // Type check
                {
                    throw SemanticError(std::format("{} is of the wrong type", value));
                }

                treePrint.push_back(1);
                printTreeString(treePrint, {"opassign", value}, false);

                SymbolType symtype = type == "Char" ? SymbolType::Char : SymbolType::Int;
                code = symtable.AddVar(Node.GetValues()[1], symtype, std::to_string(int(value[0]))); // addVar(q, C, p, val)

                Atom MOV{AtomType::MOV, std::format("'{}'", std::to_string(int(value[0]))), "", code};
                recordAtom(MOV);

                Node.GetChildren()[2].NewVal(type); // r = p

                DeclVarListList(Node.GetChildren()[2], treePrint);

                treePrint.pop_back();
                treePrint.push_back(0);
                printTreeString(treePrint, {"semicolon"}, true);
            }
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "DeclVarList'")
        {
            std::string type = Node.GetValues()[0]; // addVar(q, C, p)
            if (type == "Char")
            {
                code = symtable.AddVar(Node.GetValues()[1], SymbolType::Char);
            }
            else if (type == "Int")
            {
                code = symtable.AddVar(Node.GetValues()[1], SymbolType::Int);
            }

            Atom MOV{AtomType::MOV, "'0'", "", code};
            recordAtom(MOV);

            Node.GetChildren()[0].NewVal(Node.GetValues()[0]); // r = p

            DeclVarListList(Node.GetChildren()[0], treePrint);

            treePrint.push_back(1);
            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"semicolon"}, true);
        }
    }

    void SemanticAnalyzer::Type(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Type"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "kwchar")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"kwchar"}, true);

            Node.NewVal("Char");
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "kwint")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"kwint"}, true);

            Node.NewVal("Int");
        }
    }

    void SemanticAnalyzer::DeclVarListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"DeclVarList'"}, true);

        if (Node.IsLeaf())
        {
            return;
        }

        miniCBuilderAST::Node &initVar = Node.GetChildren()[2];
        miniCBuilderAST::Node &declVar = Node.GetChildren()[3];

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma", Node.GetChildren()[1].GetValues()[0]}, false);

        initVar.NewVal(Node.GetValues()[0]);
        initVar.NewVal(Node.GetChildren()[1].GetValues()[0]);

        InitVar(Node.GetChildren()[2], treePrint);

        declVar.NewVal(Node.GetValues()[0]);

        treePrint.pop_back();
        treePrint.push_back(0);
        DeclVarListList(Node.GetChildren()[3], treePrint);
    }

    void SemanticAnalyzer::InitVar(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"InitVar"}, true);

        std::string &name = Node.GetValues()[1];
        std::string &type = Node.GetValues()[0];

        if (Node.IsLeaf())
        {
            std::string code;

            if (type == "Char")
            {
                code = symtable.AddVar(name, SymbolType::Char);

                Atom MOV{AtomType::MOV, "'0'", "", code};
                recordAtom(MOV);
            }
            else if (type == "Int")
            {
                code = symtable.AddVar(name, SymbolType::Int);

                Atom MOV{AtomType::MOV, "'0'", "", code};
                recordAtom(MOV);
            }

            return;
        }

        miniCBuilderAST::Node &initVar = Node.GetChildren()[1];

        initVar.NewVal(type);
        initVar.NewVal(name);

        treePrint.push_back(0);
        printTreeString(treePrint, {"opassign"}, false);
        InitVarList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::InitVarList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"InitVar'"}, true);

        std::string &name = Node.GetValues()[1];
        std::string &type = Node.GetValues()[0];
        std::string code;
        std::string &value = Node.GetChildren()[0].GetValues()[0];

        if (Node.GetChildren()[0].GetLexemeType() == "num")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);

            if (type != "Int" && type != "Char") // Type check
            {
                throw SemanticError(std::format("{} is of the wrong type", value));
            }

            SymbolType symtype = type == "Char" ? SymbolType::Char : SymbolType::Int;
            code = symtable.AddVar(Node.GetValues()[1], symtype, value); // addVar(q, C, p, val)

            Atom MOV{AtomType::MOV, std::format("'{}'", value), "", code};
            recordAtom(MOV);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "chr")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, true);

            if (type != "Int" && type != "Char") // Type check
            {
                throw SemanticError(std::format("{} is of the wrong type", value));
            }

            SymbolType symtype = type == "Char" ? SymbolType::Char : SymbolType::Int;
            code = symtable.AddVar(name, symtype, std::to_string(int(value[0]))); // addVar(q, C, p, val)

            Atom MOV{AtomType::MOV, std::format("'{}'", std::to_string(int(value[0]))), "", code};
            recordAtom(MOV);
        }
    }

    void SemanticAnalyzer::ParamList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ParamList"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal("0");
            return;
        }

        treePrint.push_back(1);
        Type(Node.GetChildren()[0], treePrint);

        std::string &type = Node.GetChildren()[0].GetValues()[0];
        std::string &name = Node.GetChildren()[1].GetValues()[0];
        std::string code;

        if (type == "Char")
        {
            code = symtable.AddVar(name, SymbolType::Char);
        }
        else if (type == "Int")
        {
            code = symtable.AddVar(name, SymbolType::Int);
        }

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[1].GetValues()[0]}, false);
        ParamListList(Node.GetChildren()[2], treePrint);

        std::string n = std::to_string(std::stoi(Node.GetChildren()[2].GetValues()[0]) + 1);

        Node.NewVal(n);
    }

    void SemanticAnalyzer::ParamListList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ParamList'"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal("0");
            return;
        }

        treePrint.push_back(1);
        printTreeString(treePrint, {"comma"}, false);
        Type(Node.GetChildren()[1], treePrint);

        std::string &type = Node.GetChildren()[1].GetValues()[0];
        std::string &name = Node.GetChildren()[2].GetValues()[0];
        std::string code;

        if (type == "Char")
        {
            code = symtable.AddVar(name, SymbolType::Char);
        }
        else if (type == "Int")
        {
            code = symtable.AddVar(name, SymbolType::Int);
        }

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[2].GetValues()[0]}, false);

        ParamListList(Node.GetChildren()[3], treePrint);

        std::string n = std::to_string(std::stoi(Node.GetChildren()[3].GetValues()[0]) + 1);

        Node.NewVal(n);
    }

    void SemanticAnalyzer::StmtList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"StmtList"}, true);

        if (Node.IsLeaf())
        {
            return;
        }

        treePrint.push_back(1);
        Stmt(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        StmtList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::Stmt(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"Stmt"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "DeclareStmt")
        {
            treePrint.push_back(0);
            DeclareStmt(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "AssignOrCallOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            AssignOrCallOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "WhileOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            WhileOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "ForOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            ForOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "IfOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            IfOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "SwitchOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            SwitchOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "IOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            IOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "OOp")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(0);
            OOp(Node.GetChildren()[0], treePrint);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lbrace")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(1);
            printTreeString(treePrint, {"lbrace"}, false);

            symtable.EnterContext();
            Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
            recordAtom(ENTERCTX);
            StmtList(Node.GetChildren()[1], treePrint);
            Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
            recordAtom(EXITCTX);
            symtable.ExitContext();

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rbrace"}, true);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "kwreturn")
        {
            if (symtable.GetContext() == -1)
            {
                throw SemanticError(std::format("Operator {} should be inside function", Node.GetChildren()[0].GetLexemeType()));
            }

            treePrint.push_back(1);
            printTreeString(treePrint, {"kwreturn"}, false);

            E(Node.GetChildren()[1], treePrint);

            Atom RET{AtomType::RET, "", "", Node.GetChildren()[1].GetValues()[0]};
            recordAtom(RET);

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

    void SemanticAnalyzer::AssignOrCallOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCallOp"}, true);

        treePrint.push_back(1);
        AssignOrCall(Node.GetChildren()[0], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"semicolon"}, true);
    }

    void SemanticAnalyzer::AssignOrCall(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCall"}, true);

        treePrint.push_back(0);
        printTreeString(treePrint, {Node.GetChildren()[0].GetValues()[0]}, false);

        Node.GetChildren()[1].NewVal(Node.GetChildren()[0].GetValues()[0]);

        AssignOrCallList(Node.GetChildren()[1], treePrint);
    }

    void SemanticAnalyzer::AssignOrCallList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"AssignOrCall'"}, true);

        if (Node.GetChildren()[0].GetLexemeType() == "opassign")
        {
            treePrint.push_back(0);
            printTreeString(treePrint, {"opassign"}, false);

            std::string r = symtable.CheckVar(Node.GetValues()[0]);

            E(Node.GetChildren()[1], treePrint);

            Atom MOV{AtomType::MOV, Node.GetChildren()[1].GetValues()[0], "", r};
            recordAtom(MOV);
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            std::string &name = Node.GetValues()[0];

            treePrint.push_back(1);
            printTreeString(treePrint, {"ArgList"}, false);
            ArgList(Node.GetChildren()[1], treePrint);

            if (name == "main")
            {
                throw SemanticError("Trying to call main function");
            }

            std::string q = symtable.CheckFunc(name, Node.GetChildren()[1].GetValues()[0]);
            std::string r = symtable.Alloc();

            Atom CALL{AtomType::CALL, q, "", r};
            recordAtom(CALL);

            treePrint.pop_back();
            treePrint.push_back(0);
            printTreeString(treePrint, {"rpar"}, true);
        }
    }

    void SemanticAnalyzer::WhileOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e = Node.GetChildren()[2];

        printTreeString(treePrint, {"AssignOrCall'"}, true);

        treePrint.push_back(1);

        std::string l1 = symtable.NewLabel();

        Atom LBL1{AtomType::LBL, "", "", l1};
        recordAtom(LBL1);

        printTreeString(treePrint, {"kwwhile", "lpar"}, false);
        E(e, treePrint);

        std::string l2 = symtable.NewLabel();

        Atom EQ{AtomType::EQ, e.GetValues()[0], "'0'", l2};
        recordAtom(EQ);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rpar"}, false);

        symtable.EnterContext();
        Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
        recordAtom(ENTERCTX);
        Stmt(Node.GetChildren()[4], treePrint);
        Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
        recordAtom(EXITCTX);
        symtable.ExitContext();

        Atom JMP{AtomType::JMP, "", "", l1};
        recordAtom(JMP);

        Atom LBL2{AtomType::LBL, "", "", l2};
        recordAtom(LBL2);
    }

    void SemanticAnalyzer::ForOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &fe = Node.GetChildren()[4];

        printTreeString(treePrint, {"ForOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwfor", "lpar"}, false);

        ForInit(Node.GetChildren()[2], treePrint);

        std::string l1 = symtable.NewLabel();
        Atom LBL1{AtomType::LBL, "", "", l1};
        recordAtom(LBL1);

        printTreeString(treePrint, {"semicolon"}, false);
        ForExp(fe, treePrint);

        std::string l4 = symtable.NewLabel();
        Atom EQ{AtomType::EQ, fe.GetValues()[0], "'0'", l4};
        recordAtom(EQ);

        std::string l3 = symtable.NewLabel();
        Atom JMP1{AtomType::JMP, "", "", l3};
        recordAtom(JMP1);

        std::string l2 = symtable.NewLabel();
        Atom LBL2{AtomType::LBL, "", "", l2};
        recordAtom(LBL2);

        printTreeString(treePrint, {"semicolon"}, false);
        ForLoop(Node.GetChildren()[6], treePrint);

        Atom JMP2{AtomType::JMP, "", "", l1};
        recordAtom(JMP2);

        Atom LBL3{AtomType::LBL, "", "", l3};
        recordAtom(LBL3);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rpar"}, false);

        symtable.EnterContext();
        Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
        recordAtom(ENTERCTX);
        Stmt(Node.GetChildren()[8], treePrint);
        Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
        recordAtom(EXITCTX);
        symtable.ExitContext();

        Atom JMP3{AtomType::JMP, "", "", l2};
        recordAtom(JMP3);

        Atom LBL4{AtomType::LBL, "", "", l4};
        recordAtom(LBL4);

    }

    void SemanticAnalyzer::ForInit(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForInit"}, true);

        if (Node.IsLeaf())
        {
            return;
        }

        treePrint.push_back(0);
        AssignOrCall(Node.GetChildren()[0], treePrint);
    }

    void SemanticAnalyzer::ForExp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForExp"}, true);

        if (Node.IsLeaf())
        {
            Node.NewVal("1");
            return;
        }

        miniCBuilderAST::Node &e = Node.GetChildren()[0];

        treePrint.push_back(0);
        E(e, treePrint);

        Node.NewVal(e.GetValues()[0]);
    }

    void SemanticAnalyzer::ForLoop(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ForExp"}, true);
        if (Node.IsLeaf())
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            std::string &name = Node.GetChildren()[1].GetValues()[0];

            treePrint.push_back(0);
            printTreeString(treePrint, {"opinc", name}, true);

            std::string code = symtable.CheckVar(name);
            Atom ADD{AtomType::ADD, code, "'1'", code};
            recordAtom(ADD);
        }
        else
        {
            treePrint.push_back(0);
            AssignOrCall(Node.GetChildren()[0], treePrint);
        }
    }

    void SemanticAnalyzer::IfOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e = Node.GetChildren()[2];

        printTreeString(treePrint, {"IfOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwif", "lpar"}, false);

        E(e, treePrint);

        printTreeString(treePrint, {"rpar"}, false);

        std::string l1 = symtable.NewLabel();
        Atom EQ{AtomType::EQ, e.GetValues()[0], "'0'", l1};
        recordAtom(EQ);

        symtable.EnterContext();
        Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
        recordAtom(ENTERCTX);
        Stmt(Node.GetChildren()[4], treePrint);
        Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
        recordAtom(EXITCTX);
        symtable.ExitContext();

        std::string l2 = symtable.NewLabel();
        Atom JMP{AtomType::JMP, "", "", l2};
        recordAtom(JMP);

        Atom LBL1{AtomType::LBL, "", "", l1};
        recordAtom(LBL1);

        treePrint.pop_back();
        treePrint.push_back(0);

        ElsePart(Node.GetChildren()[5], treePrint);

        Atom LBL2{AtomType::LBL, "", "", l2};
        recordAtom(LBL2);
    }

    void SemanticAnalyzer::ElsePart(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"ElsePart"}, true);

        if (Node.IsLeaf())
        {
            return;
        }

        treePrint.push_back(0);
        printTreeString(treePrint, {"kwelse"}, false);

        symtable.EnterContext();
        Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
        recordAtom(ENTERCTX);
        Stmt(Node.GetChildren()[1], treePrint);
        Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
        recordAtom(EXITCTX);
        symtable.ExitContext();
    }

    void SemanticAnalyzer::SwitchOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &e = Node.GetChildren()[2];
        miniCBuilderAST::Node &cases = Node.GetChildren()[5];

        printTreeString(treePrint, {"SwitchOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwswitch", "lpar"}, false);

        E(e, treePrint);

        printTreeString(treePrint, {"rpar", "lbrace"}, false);

        std::string end = symtable.NewLabel();
        cases.NewVal(e.GetValues()[0]);
        cases.NewVal(end);

        Cases(cases, treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"rbrace"}, true);

        Atom LBL{AtomType::LBL, "", "", end};
        recordAtom(LBL);
    }

    void SemanticAnalyzer::Cases(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &ac = Node.GetChildren()[0];
        miniCBuilderAST::Node &c = Node.GetChildren()[1];
        std::string p = Node.GetValues()[0];
        std::string end = Node.GetValues()[1];

        printTreeString(treePrint, {"Cases"}, true);

        ac.NewVal(p);
        ac.NewVal(end);

        treePrint.push_back(1);
        ACase(ac, treePrint);

        c.NewVal(p);
        c.NewVal(end);
        c.NewVal(ac.GetValues()[2]);

        treePrint.pop_back();
        treePrint.push_back(0);

        CasesList(c, treePrint);
    }

    void SemanticAnalyzer::CasesList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        std::string p = Node.GetValues()[0];
        std::string end = Node.GetValues()[1];
        std::string def = Node.GetValues()[2];

        printTreeString(treePrint, {"Cases'"}, true);

        if (Node.IsLeaf())
        {
            std::string q;
            if (def != "NULL")
            {
                q = def;
            }
            else
            {
                q = end;
            }

            Atom JMP{AtomType::JMP, "", "", q};
            recordAtom(JMP);

            return;
        }

        miniCBuilderAST::Node &ac = Node.GetChildren()[0];
        miniCBuilderAST::Node &c = Node.GetChildren()[1];

        ac.NewVal(p);
        ac.NewVal(end);

        treePrint.push_back(1);
        ACase(ac, treePrint);

        std::string def1 = ac.GetValues()[2];
        std::string def2;
        if (def != "NULL")
        {
            if (def1 != "NULL")
            {
                throw SemanticError("Two default section");
            }

            def2 = def;
        }
        else
        {
            def2 = def1;
        }

        c.NewVal(p);
        c.NewVal(end);
        c.NewVal(def2);

        treePrint.pop_back();
        treePrint.push_back(0);
        CasesList(c, treePrint);
    }

    void SemanticAnalyzer::ACase(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        std::string next = symtable.NewLabel();
        std::string end = Node.GetValues()[1];

        printTreeString(treePrint, {"Cases'"}, true);

        treePrint.push_back(0);
        if (Node.GetChildren()[0].GetLexemeType() == "kwcase")
        {
            Node.NewVal("NULL"); // def

            std::string p = Node.GetValues()[0];
            std::string val = Node.GetChildren()[1].GetValues()[0];

            Atom NE{AtomType::NE, p, std::format("'{}'", val), next};
            recordAtom(NE);

            printTreeString(treePrint, {"kwcase", val, "colon"}, false);

            symtable.EnterContext();
            Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
            recordAtom(ENTERCTX);
            StmtList(Node.GetChildren()[3], treePrint);
            Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
            recordAtom(EXITCTX);
            symtable.ExitContext();

            Atom JMP{AtomType::JMP, "", "", end};
            recordAtom(JMP);

            Atom LBL{AtomType::LBL, "", "", next};
            recordAtom(LBL);
        }
        else
        {
            std::string def = symtable.NewLabel();

            if (Node.GetValues().size() == 3)
            {
                Node.GetValues().pop_back();
            }

            Node.NewVal(def);

            Atom JMP1{AtomType::JMP, "", "", next};
            recordAtom(JMP1);

            Atom LBL1{AtomType::LBL, "", "", def};
            recordAtom(LBL1);

            printTreeString(treePrint, {"kwdefault", "colon"}, false);

            symtable.EnterContext();
            Atom ENTERCTX{AtomType::ENTERCTX, "", "", std::to_string(symtable.GetContext())};
            recordAtom(ENTERCTX);
            StmtList(Node.GetChildren()[2], treePrint);
            Atom EXITCTX{AtomType::EXITCTX, "", "", ""};
            recordAtom(EXITCTX);
            symtable.ExitContext();

            Atom JMP2{AtomType::JMP, "", "", end};
            recordAtom(JMP2);

            Atom LBL2{AtomType::LBL, "", "", next};
            recordAtom(LBL2);
        }
    }

    void SemanticAnalyzer::IOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        std::string code = symtable.CheckVar(Node.GetChildren()[1].GetValues()[0]);

        printTreeString(treePrint, {"IOp'"}, true);

        treePrint.push_back(0);
        printTreeString(treePrint, {"kwin", Node.GetChildren()[1].GetValues()[0], "semicolon"}, true);

        Atom IN{AtomType::IN, "", "", code};
        recordAtom(IN);
    }

    void SemanticAnalyzer::OOp(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        printTreeString(treePrint, {"OOp"}, true);

        treePrint.push_back(1);
        printTreeString(treePrint, {"kwout"}, false);
        OOpList(Node.GetChildren()[1], treePrint);

        treePrint.pop_back();
        treePrint.push_back(0);
        printTreeString(treePrint, {"semicolon"}, true);
    }

    void SemanticAnalyzer::OOpList(miniCBuilderAST::Node &Node, std::vector<int> treePrint)
    {
        miniCBuilderAST::Node &child = Node.GetChildren()[0];
        printTreeString(treePrint, {"OOp'"}, true);
        std::string output;

        treePrint.push_back(0);
        if (child.GetLexemeType() == "E")
        {
            E(child, treePrint);

            output = child.GetValues()[0];
        }
        else
        {
            throw SemanticError("Strings not implemented");
        }

        Atom OUT{AtomType::OUT, "", "", output};
        recordAtom(OUT);
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
                        outputTree << finTree;
                        continue;
                    }

                    outputTree << ' ';
                }
                else
                {
                    if (i + 1 == treePrint.size())
                    {
                        outputTree << subTree;
                        continue;
                    }

                    outputTree << lineTree;
                }
            }
        }

        for (std::string node : nodes)
        {
            outputTree << node << " ";
        }

        if (newString)
        {
            prevNewString = true;
            outputTree << std::endl;
        }
        else
        {
            prevNewString = false;
        }
    }

    SemanticAnalyzer::SemanticAnalyzer(miniCBuilderAST::Node &AST) : AST{AST}
    {
        outputTree.open("./output/outputTree.tree");
        outputAtoms.open("./output/outputAtoms.atom");
        outputTable.open("./output/outputTable.table");
    }

    SemanticAnalyzer::~SemanticAnalyzer()
    {
        outputTree.close();
        outputAtoms.close();
        outputTable.close();
    }

    void SemanticAnalyzer::StartAnalysis()
    {
        StmtList(AST, {});

        outputTable << symtable;

        if (!mainCheck)
        {
            throw SemanticError("Main function is missing");
        }
    }

    void SemanticAnalyzer::recordAtom(miniCSemanticAnalyzer::Atom &atom)
    {
        if (symtable.GetContext() != -1)
        {
            functionMap[currentFunction].push_back(atom);
            outputAtoms << std::format("{}: ", symtable.GetContext()) << atom;
        }
    }

    miniCSemanticAnalyzer::SymbolTable &SemanticAnalyzer::GetSymTable()
    {
        return symtable;
    }

    std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>> &SemanticAnalyzer::GetFunctionMap()
    {
        return functionMap;
    }
}