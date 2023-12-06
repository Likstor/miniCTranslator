#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "miniCLexicalAnalyzer.h"
#include <unordered_map>
#include <ctype.h>

Lexer::Lexer(std::ifstream &stream, const std::unordered_map<ll, edgesMap> &graph, std::unordered_map<std::string, std::string> &keywordsList)
{
    lexicalGraph = graph;
    keywords = keywordsList;

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

    for (int i = 0; i != -1; i++)
    {
        Token temp = Lexer::getNextLexem(stream);

        std::cout << "[" << temp.token << ", \"" << temp.value << "\"]" << std::endl;

        if (temp.token == "error" || temp.token == "eof")
        {
            break;
        }
    }
}

Token Lexer::getNextLexem(std::ifstream &stream)
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
            if (cache == "letter" || cache == "digit")
            {
                buffer.append(subCache);
            }
            else
            {
                buffer.append(cache);
            }
        }

        if (currentEdge.read)
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

        // Обработка дополнительных команд "command|Token"
        std::size_t pos = currentEdge.lexem.find('|');
        if (pos != std::string::npos)
        {
            std::string command = currentEdge.lexem.substr(0, pos);

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

            currentEdge.lexem.erase(0, pos + 1);
        }

        if (currentEdge.lexem.empty()) // Проверка необходимости генерации лексемы
        {
            continue;
        }
        else if (currentEdge.lexem == "id" && keywords.contains(buffer))
        {
            Token temp = {keywords[buffer], ""};

            buffer.clear();

            return temp;
        }
        else if (currentEdge.lexem != "error")
        {
            {
                Token temp = {currentEdge.lexem, buffer};

                buffer.clear();

                return temp;
            }
        }
        else
        {
            Token temp = {currentEdge.lexem, ""};

            buffer.clear();

            return temp;
        }
    }
}