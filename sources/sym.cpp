#pragma once
#include <sym.h>
#include <miniCLexer/lexer.h>
#include <string>
#include <deque>
#include <vector>
#include <iostream>

ShuntingYardMachine::ShuntingYardMachine(miniCLexer::Lexer &lexer): lexer{lexer} {};

std::vector<miniCLexer::Token> ShuntingYardMachine::getReversePolishNotation() 
{
    std::deque<miniCLexer::Token> stack;
    std::vector<miniCLexer::Token> output;

    miniCLexer::Token lexeme;
    while (true)
    {
        lexeme = lexer.getNextLexem();

        if (lexeme.token == "eof") {
            break;
        }

        if (lexeme.token == "num") 
        {
            output.push_back(lexeme);
        }
        else if (lexeme.token == "lpar")
        {
            stack.push_back(lexeme);
        }
        else if (lexeme.token == "rpar")
        {
            while (stack.back().token != "lpar") {
                output.push_back(stack.back());
                stack.pop_back();

                if (stack.empty())
                {
                    return {{"error", ""}};
                }
            }
            stack.pop_back();
        }
        else
        {
            if (stack.size() == 0 || stack.back().token == "lpar") 
            {
                stack.push_back(lexeme);
            }
            else if (operators[stack.back().token].priority < operators[lexeme.token].priority) 
            {
                stack.push_back(lexeme);
            }
            else
            {
                while (operators[stack.back().token].priority > operators[lexeme.token].priority ||
                    (operators[stack.back().token].priority == operators[lexeme.token].priority && 
                    operators[stack.back().token].associative == "LEFT")) {
                    if (stack.back().token == "lpar") {
                        break;
                    }
                    output.push_back(stack.back());
                    stack.pop_back();

                    if (stack.empty())
                    {
                        break;
                    }
                }
                stack.push_back(lexeme);
            }
        }
    }
    
    while (!stack.empty()) {
        miniCLexer::Token temp = stack.back();
        stack.pop_back();
        if (temp.token == "lpar")
        {
            return {{"error", ""}};
        }
        output.push_back(temp);
    }

    return output;
}