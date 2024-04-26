#pragma once
#include <miniCBuilderAST/builder.h>
#include <miniCBuilderAST/node.h>
#include <algorithm>

namespace miniCBuilderAST
{
    Builder::Builder(miniCLexer::Lexer &lexer, CanonicalTable &table) : Lexer{lexer}, Table{table}
    {
        StackStates.push(0);
    }

    bool Builder::BuildAST()
    {
        miniCLexer::Token curToken = Lexer.getNextToken();
        while (true)
        {
            if (curToken.LexemeType == "error") {
                return false;
            }

            int curState = StackStates.top();
            Action action = Table.Action[curState][curToken.LexemeType];

            if (action.ActionType == "shift")
            {
                StackStates.push(action.Pos);
                miniCBuilderAST::Node tempNode{curToken.LexemeType, {curToken.Value}};
                StackNode.push(tempNode);

                curToken = Lexer.getNextToken();
                continue;
            }

            if (action.ActionType == "reduce")
            {
                std::vector<miniCBuilderAST::Node> tempArrayNode;

                for (int i = 0; i < action.Rule.Body.size(); i++)
                {
                    StackStates.pop();

                    miniCBuilderAST::Node tempNode = StackNode.top();
                    tempArrayNode.push_back(tempNode);
                    StackNode.pop();
                }

                std::reverse(tempArrayNode.begin(), tempArrayNode.end());
                miniCBuilderAST::Node tempNode{action.Rule.Name, {}, tempArrayNode};

                StackNode.push(tempNode);
                StackStates.push(Table.Goto[StackStates.top()][action.Rule.Name]);
                continue;
            }

            if (action.ActionType == "accept")
            {
                AST = StackNode.top();
                return true;
            }

            if (action.ActionType == "error")
            {
                return false;
            }
        }
    }

    std::pair<Node, bool> Builder::GetAST()
    {
        if (AST.GetLexemeType() == "NONE")
        {
            bool ok = BuildAST();
            if (ok) {
                return {AST, true};
            }
            else{
                return {AST, false};
            }
        }

        return {AST, true};
    }
}