#pragma once
#include <miniCSemanticAnalyzer/symtable.h>
#include <miniCSemanticAnalyzer/exception.h>
#include <format>

namespace miniCSemanticAnalyzer
{
    SymbolTable::SymbolTable(){};

    SymbolData &SymbolTable::GetSymbolData(std::string code)
    {
        return data[std::stoi(code)];
    }

    std::pair<std::string, bool> SymbolTable::findSymbolData(std::string name)
    {
        for (int i = int(contextArray.size()); i >= 0; i--)
        {
            auto [code, ok] = subData[contextArray[i]][std::format("c%d_", contextArray[i]) + name];
            if (ok)
            {
                return {std::to_string(code), ok};
            }
        }

        return {"NULL", false};
    }

    std::string SymbolTable::Alloc()
    {
        SymbolData temp{
            "#DEV_" + std::to_string(currentCode),
            SymbolClass::Dev,
            SymbolType::Dev,
            "NULL",
            "NULL"};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return "#DEV_" + std::to_string(currentCode++);
    }

    void SymbolTable::EnterContext()
    {
        contextArray.push_back(currentContext++);
    }

    void SymbolTable::ExitContext()
    {
        contextArray.pop_back();
    }

    std::string SymbolTable::NewLabel()
    {
        return "#LABEL_" + std::to_string(currentLabel++);
    }

    std::string SymbolTable::CheckVar(std::string name)
    {
        auto [code, ok] = findSymbolData("var_" + name);
        if (ok)
        {
            return code;
        }

        throw SemanticError("Unknown variable: " + name);
    }

    std::string SymbolTable::AddVar(std::string name, SymbolType type, std::string init)
    {
        SymbolData temp{
            "c" + std::to_string(contextArray.back()) + "_var_" + name,
            SymbolClass::Var,
            type,
            NULL,
            init};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return std::to_string(currentCode++);
    }

    std::string SymbolTable::CheckFunc(std::string name, std::string len)
    {
        auto [code, ok] = findSymbolData("func_" + name + "_" + len);
        if (ok)
        {
            return code;
        }

        throw SemanticError("Unknown function: " + name);
    }

    std::string SymbolTable::AddFunc(std::string name, SymbolType type, std::string len)
    {
        SymbolData temp{
            "c" + std::to_string(contextArray.back()) + "_func_" + name + "_" + len,
            SymbolClass::Func,
            type,
            len,
            NULL};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return std::to_string(currentCode++);
    }
}