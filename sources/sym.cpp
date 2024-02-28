#pragma once
#include <sym.h>
#include <miniCLexer/lexer.h>
#include <string>
#include <stack>
#include <vector>
#include <iostream>

ShuntingYardMachine::ShuntingYardMachine(miniCLexer::Lexer &lexer) : lexer{lexer} {};

std::vector<miniCLexer::Token> ShuntingYardMachine::getReversePolishNotation()
{
    std::stack<miniCLexer::Token> stack;
    std::vector<miniCLexer::Token> output;

    miniCLexer::Token lexeme;
    while (true)
    {
        lexeme = lexer.getNextLexem();

        if (lexeme.token == "eof")
        {
            break;
        }

        if (lexeme.token == "num")
        {
            output.push_back(lexeme);
        }
        else if (lexeme.token == "lpar")
        {
            stack.push(lexeme);
        }
        else if (lexeme.token == "rpar")
        {
            while (stack.top().token != "lpar")
            {
                output.push_back(stack.top());
                stack.pop();

                if (stack.empty())
                {
                    return {{"error", ""}};
                }
            }
            stack.pop();
        }
        else
        {
            if (stack.size() == 0 || stack.top().token == "lpar")
            {
                stack.push(lexeme);
            }
            else if (operators[stack.top().token].priority < operators[lexeme.token].priority)
            {
                stack.push(lexeme);
            }
            else
            {
                while (operators[stack.top().token].priority > operators[lexeme.token].priority ||
                    (operators[stack.top().token].priority == operators[lexeme.token].priority &&
                        operators[stack.top().token].associative == "LEFT"))
                {
                    if (stack.top().token == "lpar")
                    {
                        break;
                    }
                    output.push_back(stack.top());
                    stack.pop();

                    if (stack.empty())
                    {
                        break;
                    }
                }
                stack.push(lexeme);
            }
        }
    }

    while (!stack.empty())
    {
        miniCLexer::Token temp = stack.top();
        stack.pop();
        if (temp.token == "lpar")
        {
            return {{"error", ""}};
        }
        output.push_back(temp);
    }

    return output;
}