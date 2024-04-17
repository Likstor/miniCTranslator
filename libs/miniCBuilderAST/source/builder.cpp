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

    void Builder::BuildAST()
    {
        miniCLexer::Token curToken = Lexer.getNextToken();
        while (true)
        {
            int curState = StackStates.top();
            std::cout << curState << curToken.LexemeType << std::endl;
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
                std::cout << "ACCEPT " << std::endl;
                return;
            }

            if (action.ActionType == "error")
            {
                std::cout << "ERROR" << std::endl;
                return;
            }
        }
    }

    Node Builder::GetAST()
    {
        if (AST.GetLexemeType() == "NONE")
        {
            BuildAST();
        }

        return AST;
    }
}