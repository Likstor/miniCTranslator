#pragma once
#include <miniCBuilderAST/node.h>

namespace miniCSemanticAnalyzer 
{
    void E(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E7(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E7List(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E6(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E6List(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E5(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E5List(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E4(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E4List(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E3(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E3List(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E2(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E1(miniCBuilderAST::Node Node, std::vector<int> treePrint);
    void E1List(miniCBuilderAST::Node Node, std::vector<int> treePrint);

    void printTreeString(std::vector<int> treePrint);
}