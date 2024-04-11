#include <vector>
#include <string>
#include <unordered_map>
#include <miniCLexer/lexer.h>
#include <stack>
#include <iostream>

namespace miniCBuilderAST
{
    struct Rule
    {
        std::string LeftPart;
        std::vector<miniCLexer::Token> RightPart;
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
        std::stack<miniCLexer::Token> StackTokens;
        std::stack<int> StackStates;

    public:
        Builder(miniCLexer::Lexer &table, CanonicalTable &Table);
        void BuildAST();
    };
}
