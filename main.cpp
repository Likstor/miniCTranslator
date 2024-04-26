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
    std::ifstream stream(argv[1], std::ios::in);

    miniCLexer::Lexer lexer{stream};

    std::ifstream json(argv[2], std::ios::in);

    auto canonicalTableJson = nlohmann::ordered_json::parse(json);

    miniCBuilderAST::CanonicalTable CT;

    CT.Terminals = canonicalTableJson["Terminals"];
    CT.Nonterminals = canonicalTableJson["NonTerminals"];

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
            action.Pos = canonicalTableJson["Action"][key][term]["NextState"];

            if (canonicalTableJson["Action"][key][term]["Rule"]["Name"] == "NULL")
            {
                action.Rule = miniCBuilderAST::Rule{};
            }
            else
            {
                miniCBuilderAST::Rule rule;

                rule.Name = canonicalTableJson["Action"][key][term]["Rule"]["Name"];

                for (int i = 0; i < canonicalTableJson["Action"][key][term]["Rule"]["Body"].size(); i++)
                {
                    rule.Body.push_back(miniCLexer::Token{canonicalTableJson["Action"][key][term]["Rule"]["Body"][i], ""});
                }

                action.Rule = rule;
            }
            CT.Action[std::stoi(key)][term] = action;
        }
    }
    miniCBuilderAST::Builder bld{lexer, CT};

    std::pair<miniCBuilderAST::Node, bool> AST = bld.GetAST();

    if (AST.second)
    {
        std::cout << "ACCEPT" << std::endl;

        miniCSemanticAnalyzer::SemanticAnalyzer SA{AST.first};
        SA.StartAnalysis();
    }
    else
    {
        std::cout << "ERROR" << std::endl;
    }
}
