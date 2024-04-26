#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <miniCLexer/lexer.h>
#include <miniCBuilderAST/node.h>
#include <stack>
#include <iostream>
#include <any>

namespace miniCBuilderAST
{
    struct Rule
    {
        std::string Name;
        std::vector<miniCLexer::Token> Body;
    };

    struct Action
    {
        std::string ActionType;
        int Pos;
        Rule Rule;
    };

    struct CanonicalTable
    {
        std::unordered_map<int, std::unordered_map<std::string, int>> Goto;
        std::unordered_map<int, std::unordered_map<std::string, Action>> Action;
        int StartPos;
        std::vector<std::string> Terminals;
        std::vector<std::string> Nonterminals;
    };

    class Builder
    {
    private:
        miniCLexer::Lexer Lexer;
        CanonicalTable Table;
        std::stack<miniCBuilderAST::Node> StackNode;
        std::stack<int> StackStates;
        Node AST{"NONE", {}};

    public:
        Builder(miniCLexer::Lexer &table, CanonicalTable &Table);
        bool BuildAST();
        std::pair<Node, bool> GetAST();
    };
}
