#pragma once
#include <miniCSemanticAnalyzer/symtable.h>
#include <miniCSemanticAnalyzer/exception.h>
#include <format>
#include <iomanip>
#include <sstream>

namespace miniCSemanticAnalyzer
{
    SymbolTable::SymbolTable(){};

    SymbolData &SymbolTable::GetSymbolData(std::string code)
    {
        return data[std::stoi(code)];
    }

    int SymbolTable::GetContext()
    {
        return contextArray.back();
    }

    std::pair<std::string, bool> SymbolTable::findSymbolData(std::string name)
    {
        for (int i = int(contextArray.size()); i >= 0; i--)
        {
            auto [code, ok] = subData[contextArray[i]][std::format("c{}_", contextArray[i]) + name];
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
            "#TEMP_" + std::to_string(currentCode),
            SymbolClass::Dev,
            SymbolType::Int,
            "NULL",
            "NULL"};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return std::to_string(currentCode++);
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

    std::string fill(size_t len)
    {
        std::string output;

        for (size_t i = 0; i < len; i++)
        {
            output += "─";
        }

        return output;
    }

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable)
    {
        size_t codeLen = 4;
        size_t nameLen = 4;
        size_t classLen = 5;
        size_t typeLen = 4;
        size_t lenLen = 3;
        size_t initLen = 4;
        size_t offsetLen = 6;
        size_t temp = 0;

        std::string coll = "│ ";
        std::string colr = " │";
        std::string col = " │ ";

        auto prepateData = [=](int len, std::string data, std::string orient = "left")
        {
            std::stringstream temp;

            if (orient == "left")
            {
                temp << std::left;
            }
            else if (orient == "right")
            {
                temp << std::right;
            }

            temp << std::setw(len) << data;
            return temp.str();
        };

        auto fill = [](size_t len)
        {
            std::string output;

            for (size_t i = 0; i < len; i++)
            {
                output += "─";
            }

            return output;
        };

        for (auto [code, sd] : symtable.data)
        {
            temp = std::to_string(code).size();
            codeLen = temp > codeLen ? temp : codeLen;

            temp = sd.Name.size();
            nameLen = temp > nameLen ? temp : nameLen;

            temp = std::to_string(int(sd.Class)).size();
            classLen = temp > classLen ? temp : classLen;

            temp = std::to_string(int(sd.Type)).size();
            typeLen = temp > typeLen ? temp : typeLen;

            temp = sd.Len.size();
            lenLen = temp > lenLen ? temp : lenLen;

            temp = sd.Init.size();
            initLen = temp > initLen ? temp : initLen;

            temp = sd.Offset.size();
            offsetLen = temp > offsetLen ? temp : offsetLen;
        }

        std::stringstream sep;
        sep << "├" << fill(codeLen + 2) << "┼" << fill(nameLen + 2) << "┼" << fill(classLen + 2) << "┼" << fill(typeLen + 2) << "┼" << fill(lenLen + 2) << "┼" << fill(initLen + 2) << "┼" << fill(offsetLen + 2) << "┤" << std::endl;

        std::stringstream top;
        top << "┌" << fill(codeLen + 2) << "┬" << fill(nameLen + 2) << "┬" << fill(classLen + 2) << "┬" << fill(typeLen + 2) << "┬" << fill(lenLen + 2) << "┬" << fill(initLen + 2) << "┬" << fill(offsetLen + 2) << "┐" << std::endl;

        std::stringstream bottom;
        bottom << "└" << fill(codeLen + 2) << "┴" << fill(nameLen + 2) << "┴" << fill(classLen + 2) << "┴" << fill(typeLen + 2) << "┴" << fill(lenLen + 2) << "┴" << fill(initLen + 2) << "┴" << fill(offsetLen + 2) << "┘" << std::endl;

        os << top.str();
        os << coll << prepateData(codeLen, "Code") << col << prepateData(nameLen, "Name") << col << prepateData(classLen, "Class") << col << prepateData(typeLen, "Type") << col << prepateData(lenLen, "Len") << col << prepateData(initLen, "Init") << col << prepateData(offsetLen, "Offset") << colr << std::endl;
        os << sep.str();

        for (auto [code, sd] : symtable.data)
        {
            os << coll << prepateData(codeLen, std::to_string(code), "right") << col << prepateData(nameLen, sd.Name) << col << prepateData(classLen, sd.GetClass()) << col << prepateData(typeLen, sd.GetType()) << col << prepateData(lenLen, sd.Len) << col << prepateData(initLen, sd.Init, "right") << col << prepateData(offsetLen, sd.Offset) << colr << std::endl;
        }

        os << bottom.str();

        return os;
    }
}