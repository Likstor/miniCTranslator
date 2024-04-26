#pragma once
#include <miniCBuilderAST/node.h>

namespace miniCBuilderAST
{
    Node::Node(std::string lexemeType, std::vector<std::string> values, std::vector<Node> children) : lexemeType{lexemeType}, values{values}, children{children} {}

    Node::Node(std::string lexemeType, std::vector<std::string> values) : lexemeType{lexemeType}, values{values} {}

    bool Node::IsLeaf()
    {
        return children.size() == 0 ? true : false;
    }

    std::vector<std::string> Node::GetValues()
    {
        return values;
    }

    std::vector<Node> Node::GetChildren()
    {
        return children;
    }

    std::string Node::GetLexemeType()
    {
        return lexemeType;
    }
}