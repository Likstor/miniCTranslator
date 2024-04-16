#pragma once
#include <string>
#include <vector>
#include <any>

namespace miniCBuilderAST
{
    class Node
    {
    private:
        std::string lexemeType;
        std::vector<std::any> values;
        std::vector<Node> children;

    public:
        Node(std::string lexemeType, std::vector<std::any> values, std::vector<Node> children);
        Node(std::string lexemeType, std::vector<std::any> values);

        bool IsLeaf();
        std::string GetLexemeType();
        std::vector<std::any> GetValues();
        std::vector<Node> GetChildren();
    };
}