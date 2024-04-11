#include <miniCBuilderAST/builder.h>

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

            Action action = Table.Action[curState][curToken.LexemeType];

            if (action.ActionType == "shift")
            {
                StackStates.push(action.Pos);
                curToken = Lexer.getNextToken();
                continue;
            }

            if (action.ActionType == "reduce")
            {
                for (int i = 0; i < action.Rule.RightPart.size(); i++)
                {
                    StackStates.pop();
                }
                StackStates.push(Table.Goto[StackStates.top()][action.Rule.LeftPart]);
                continue;
            }

            if (action.ActionType == "accept")
            {
                std::cout << "ACCEPT" << std::endl;
                return;
            }

            if (action.ActionType == "error")
            {
                std::cout << "ERROR" << std::endl;
                return;
            }
        }
    }
}