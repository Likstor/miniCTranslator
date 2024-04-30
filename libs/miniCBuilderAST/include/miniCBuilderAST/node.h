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
        std::vector<std::string> values;
        std::vector<Node> children;

    public:
        Node(std::string lexemeType, std::vector<std::string> values, std::vector<Node> children);
        Node(std::string lexemeType, std::vector<std::string> values);

        bool IsLeaf();
        std::string GetLexemeType();
        std::vector<std::string> &GetValues();
        std::vector<Node>& GetChildren();
        void NewVal(std::string val);
    };
}