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
#include <miniCSemanticAnalyzer/exception.h>
#include <miniCAtomsToIntel8080/translator.h>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    std::cout << std::endl
              << "Translator of the MiniC language into the Intel 8080 assembler." << std::endl << std::endl;

        if (argc < 3)
    {
        std::cout << "Enter the path to the file with the code and the file with the canonical table." << std::endl
                  << "Format: \"miniCTranslator.exe [code file] [canonical table json]\"" << std::endl
                  << "Example: \"miniCTranslator.exe ./code.minic ./canonicalTable.json\"" << std::endl;
        return -1;
    }

    std::cout << "Translation started..." << std::endl;

    std::ifstream stream(argv[1], std::ios::in);

    miniCBuilderAST::CanonicalTable CT;

    try 
    {
        // JSON PARSE
        std::ifstream json(argv[2], std::ios::in);

        auto canonicalTableJson = nlohmann::ordered_json::parse(json);

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
    }
    catch (...)
    {
        std::cout << "JSON parse \033[1;31merror\033[0m" << std::endl;
        return -1;
    }
    
    // JSON PARSE

    miniCLexer::Lexer lexer{stream};

    miniCBuilderAST::Builder bld{lexer, CT};

    std::cout << "Lexical and syntax analysis status: ";

    std::pair<miniCBuilderAST::Node, bool> AST = bld.GetAST();

    if (AST.second)
    {
        std::cout << "\033[1;32mACCEPT\033[0m" << std::endl;

        miniCSemanticAnalyzer::SemanticAnalyzer SA{AST.first};

        std::cout << "Semantic analysis status: ";
        try
        {
            SA.StartAnalysis();
            std::cout << "\033[1;32mACCEPT\033[0m" << std::endl;
        }
        catch (miniCSemanticAnalyzer::SemanticError e)
        {
            std::cout << "\033[1;31mERROR\033[0m" << std::endl;

            std::cerr <<  e.what() << std::endl;
            return -1;
        }

        miniCAtomsToIntel8080::Translator Translator{SA.GetSymTable(), SA.GetFunctionMap()};

        Translator.Translate();

        std::cout << "Translation complete. The result files is located in \"./output/\"" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31mERROR\033[0m" << std::endl;
    }
}
