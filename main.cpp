#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <json.hpp>
#include <typeinfo>
#include <miniCLexer/lexer.h>
#include <miniCBuilderAST/builder.h>
#include <miniCBuilderAST/node.h>
#include <miniCSemanticAnalyzer/analyzer.h>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     std::cerr << "None file path";
    //     return -1;
    // }

    std::ifstream stream(argv[1], std::ios::in);

    miniCLexer::Lexer lexer{stream};

    // while (true)
    // {
    //     miniCLexer::Token temp = lexer.getNextToken();

    //     std::cout << "[" << temp.LexemeType << ", \"" << temp.Value << "\"]" << std::endl;

    //     if (temp.LexemeType == "error" || temp.LexemeType == "eof")
    //     {
    //         break;
    //     }

    // }

    std::ifstream json(argv[2], std::ios::in);

    auto canonicalTableJson = nlohmann::ordered_json::parse(json);

    miniCBuilderAST::CanonicalTable CT;

    CT.Terminals = canonicalTableJson["Terminals"];
    CT.Nonterminals = canonicalTableJson["Nonterminals"];

    for (const auto &[key, value] : canonicalTableJson["Goto"].items())
    {
        CT.Goto[std::stoi(key)] = value;
    }

    for (const auto &[key, value] : canonicalTableJson["Action"].items())
    {
        for (auto term : CT.Terminals)
        {
            miniCBuilderAST::Action action;
            action.ActionType = canonicalTableJson["Action"][key][term]["ActionType"];
            action.Pos = canonicalTableJson["Action"][key][term]["Pos"];

            if (canonicalTableJson["Action"][key][term]["Rule"]["LeftPart"] == "NULL")
            {
                action.Rule = miniCBuilderAST::Rule{};
            }
            else
            {
                miniCBuilderAST::Rule rule;

                rule.LeftPart = canonicalTableJson["Action"][key][term]["Rule"]["LeftPart"];

                for (int i = 0; i < canonicalTableJson["Action"][key][term]["Rule"]["RightPart"].size(); i++)
                {
                    rule.RightPart.push_back(miniCLexer::Token{canonicalTableJson["Action"][key][term]["Rule"]["RightPart"][i]["LexemeType"], canonicalTableJson["Action"][key][term]["Rule"]["RightPart"][i]["Value"]});
                }

                action.Rule = rule;
            }
            CT.Action[std::stoi(key)][term] = action;
        }
    }
    miniCBuilderAST::Builder bld{lexer, CT};

    bld.BuildAST();

    miniCBuilderAST::Node AST = bld.GetAST();

    miniCSemanticAnalyzer::E(AST, {});
}
