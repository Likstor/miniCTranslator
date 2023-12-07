#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <ctype.h>
#include <lexer.h>

Lexer::Lexer(std::string file, 
            const std::unordered_map<ll, edgesMap> &graph, 
            std::unordered_map<std::string, std::string> &keywordsList)
{
    lexicalGraph = graph;
    keywords = keywordsList;
    stream.open(file, std::ios::in);

    read();
}

void Lexer::read()
{
    if (stream.peek() == EOF)
    {
        cache = "eof";
    }
    else if (std::isalpha(stream.peek()))
    {
        subCache = stream.get();
        cache = "letter";
    }
    else if (std::isdigit(stream.peek()))
    {
        subCache = stream.get();
        cache = "digit";
    }
    else
    {
        cache = stream.get();
    }
}

void Lexer::append()
{
    if (cache == "letter" || cache == "digit")
    {
        buffer.append(subCache);
    }
    else
    {
        buffer.append(cache);
    }
}

void Lexer::runCommand(std::string command, edge currentEdge)
{
    if (command == "clear")
    {
        buffer.clear();
    }
    else if (command == "debug")
    {
        std::cout << "\033[1;33m-----DEBUG-START-----\033[0m" << std::endl;
        std::cout << "Current cache: " << cache << std::endl;
        std::cout << "Current sub cache: " << subCache << std::endl;
        std::cout << "Current state: " << currentState << std::endl;
        std::cout << "Buffer: " << buffer << std::endl;
        std::cout << "Save previous symbol: " << currentEdge.append << std::endl;
        std::cout << "Read next symbol: " << currentEdge.read << std::endl;
        if (!currentEdge.lexem.empty())
        {
            std::cout << "Lexem: " << currentEdge.lexem << std::endl;
        }
        std::cout << "\033[1;33m-----DEBUG-END-------\033[0m" << std::endl;
    }
}

Token Lexer::createToken(std::string lexem, std::string value)
{
    Token res = {lexem, value};
    buffer.clear();

    return res;
}

Token Lexer::getNextLexem()
{
    while (true)
    {
        edge currentEdge;

        if (lexicalGraph[currentState].contains(cache)) // Проверка наличия особого условия для считанного символа
        {
            currentEdge = lexicalGraph[currentState][cache];
        }
        else
        {
            currentEdge = lexicalGraph[currentState]["default"];
        }

        currentState = currentEdge.nextState;

        if (currentEdge.append) // Проверка необходимости добавления в буффер
        {
            append();
        }

        if (currentEdge.read)
        {
            read();
        }

        // Обработка дополнительных команд "command|Token"
        std::size_t pos = currentEdge.lexem.find('|');
        if (pos != std::string::npos)
        {
            std::string command = currentEdge.lexem.substr(0, pos);
            currentEdge.lexem.erase(0, pos + 1);
            runCommand(command, currentEdge);
        }

        if (currentEdge.lexem.empty()) // Проверка необходимости генерации лексемы
        {
            continue;
        }
        else if (currentEdge.lexem == "id" && keywords.contains(buffer))
        {
            Token res = createToken(keywords[buffer], "");
            return res;
        }
        else if (currentEdge.lexem != "error")
        {
            {
                Token res = createToken(currentEdge.lexem, buffer);
                return res;
            }
        }
        else
        {
            Token res = createToken(currentEdge.lexem, "");
            return res;
        }
    }
}