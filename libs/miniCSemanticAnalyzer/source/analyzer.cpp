#pragma once
#include <miniCSemanticAnalyzer/analyzer.h>
#include <miniCBuilderAST/node.h>
#include <iostream>

namespace miniCSemanticAnalyzer
{
    void E(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E7(Node.GetChildren()[0], {});
    }

    void E7(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E6(Node.GetChildren()[0], {});
        E7List(Node.GetChildren()[1], {});
    }

    void E7List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opor")
        {
            E6(Node.GetChildren()[1], {});
            E7List(Node.GetChildren()[2], {});
        }
    }

    void E6(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E5(Node.GetChildren()[0], {});
        E6List(Node.GetChildren()[1], {});
    }

    void E6List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opand")
        {
            E5(Node.GetChildren()[1], {});
            E6List(Node.GetChildren()[2], {});
        }
    }

    void E5(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E4(Node.GetChildren()[0], {});
        E5List(Node.GetChildren()[1], {});
    }

    void E5List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opeq")
        {
            E4(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opne")
        {
            E4(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "oplt")
        {
            E4(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opgt")
        {
            E4(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "ople")
        {
            E4(Node.GetChildren()[1], {});
        }
    }

    void E4(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E3(Node.GetChildren()[0], {});
        E4List(Node.GetChildren()[1], {});
    }

    void E4List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opplus")
        {
            E3(Node.GetChildren()[1], {});
            E4List(Node.GetChildren()[2], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opminus")
        {
            E3(Node.GetChildren()[1], {});
            E4List(Node.GetChildren()[2], {});
        }
    }

    void E3(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        E2(Node.GetChildren()[0], {});
        E3List(Node.GetChildren()[1], {});
    }

    void E3List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opmul")
        {
            E2(Node.GetChildren()[1], {});
            E3List(Node.GetChildren()[2], {});
        }
    }

    void E2(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren()[0].GetLexemeType() == "opnot")
        {
            E1(Node.GetChildren()[1], {});
        }
        else
        {
            E1(Node.GetChildren()[0], {});
        }
    }

    void E1(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren()[0].GetLexemeType() == "id")
        {
            E1List(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "num")
        {
            std::cout << "TEST NUM ";
            auto tmp = std::any_cast<std::vector<std::any>>(Node.GetChildren()[0].GetValues()[0]);
            auto tmp2 = std::any_cast<std::string>(tmp[0]);
            std::cout << tmp2 << std::endl;
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "lpar")
        {
            E(Node.GetChildren()[1], {});
        }
        else if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
            // id
        }
    }

    void E1List(miniCBuilderAST::Node Node, std::vector<int> treePrint)
    {
        if (Node.GetChildren().size() == 0)
        {
            return;
        }

        if (Node.GetChildren()[0].GetLexemeType() == "opinc")
        {
        }
    }

    void printTreeString(std::vector<int> treePrint, miniCBuilderAST::Node Node)
    {
    }
}