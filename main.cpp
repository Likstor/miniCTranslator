#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <lexer.h>
#include <json.hpp>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "None file path";
        return -1;
    }

    std::ifstream config(argv[1]);
    json data = json::parse(config);

    std::unordered_map<std::string, std::string> keywords;
    std::unordered_map<ll, edgesMap> lexicalGraph;

    for (auto&& [word, keyword] : data["lexerConfig"]["keywords"].items())
    {
        keywords[word] = keyword;
    }

    for (auto&& [state, _] : data["lexerConfig"]["lexicalGraph"].items())
    {
        for (auto &&[chr, edge] : data["lexerConfig"]["lexicalGraph"][state].items())
        {
            lexicalGraph[std::stoi(state)][chr] = {edge[0], edge[1], edge[2], edge[3]};
        }
    }

    Lexer lexer(argv[2], lexicalGraph, keywords);

    for (int i = 0; i != -1; i++)
    {
        Token temp = lexer.getNextLexem();

        std::cout << "[" << temp.token << ", \"" << temp.value << "\"]" << std::endl;

        if (temp.token == "error" || temp.token == "eof")
        {
            break;
        }
    }
}