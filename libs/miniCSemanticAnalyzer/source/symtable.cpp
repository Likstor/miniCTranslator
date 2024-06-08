#pragma once
#include <miniCSemanticAnalyzer/symtable.h>
#include <miniCSemanticAnalyzer/exception.h>
#include <miniCSemanticAnalyzer/atom.h>
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

    std::unordered_map<int, Context> &SymbolTable::GetContextMap()
    {
        return contextMap;
    }

    std::pair<std::string, bool> SymbolTable::findSymbolData(std::string name)
    {
        for (int i = int(contextArray.size()) - 1; i >= 0; i--)
        {
            auto [code, ok] = subData[contextArray[i]][name];
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
            GetContext(),
            SymbolKind::Var,
            SymbolType::Int,
            "NULL",
            "NULL"};

        // Записываем информацию в таблицу для быстрого доступа
        subData[contextArray.back()][temp.Name] = {currentCode, true};
        // Записываем информацию в таблицу символов
        data[currentCode] = temp;

        // Добавляем переменную в текущий контекст
        AddVarToContext(currentCode);

        return std::to_string(currentCode++);
    }

    void SymbolTable::EnterContext()
    {
        // Добавляем в contextArray новый контекст и обновляем maxContext
        contextArray.push_back(maxContext++);
    }

    void SymbolTable::ExitContext()
    {
        // Заполняем offset для переменных этого контекста
        FillOffset();
        // Снимаем номер текущего контекста со "стека"
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
        auto [code, ok] = findSymbolData("var_" + name);
        if (ok)
        {
            throw SemanticError(std::format("Attempt to reinitialize a variable {}", name));
        }

        SymbolData temp{
            "var_" + name,
            GetContext(),
            SymbolKind::Var,
            type,
            "NULL",
            init};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        AddVarToContext(currentCode);

        return std::to_string(currentCode++);
    }

    std::string SymbolTable::CheckFunc(std::string name, std::string len)
    {
        auto [code, ok] = findSymbolData(std::format("func_{}_{}", name, len));
        if (ok)
        {
            return code;
        }

        throw SemanticError("Unknown function: " + name);
    }

    std::string SymbolTable::AddFunc(std::string name, SymbolType type, std::string len)
    {
        auto [code, ok] = findSymbolData(std::format("func_{}_{}", name, len));
        if (ok)
        {
            throw SemanticError("Trying to override a function: " + name);
        }

        SymbolData temp{
            std::format("func_{}_{}", name, len),
            -1,
            SymbolKind::Func,
            type,
            len,
            "NULL"};

        subData[-1][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return std::to_string(currentCode++);
    }

    void SymbolTable::AddVarToContext(int var)
    {
        // Добавляем переданный код
        contextMap[GetContext()].Vars.push_back(var);
        // Обновляем количество переменных
        contextMap[GetContext()].Len += 1;
    }

    void SymbolTable::FillOffset()
    {
        // Получем информацию о текущем контексте
        Context &ctxInfo = contextMap[GetContext()];

        for (size_t i = 0; i < ctxInfo.Len; i++)
        {
            // -2 - это условный код (костыль), который используется
            // для учета сдвига для кода возврата и возвращаемого значения
            // На таблицу никак не влияет
            if (ctxInfo.Vars[i] == -2)
            {
                continue;
            }

            // Получаем ссылку на информацию о переменной
            SymbolData &tempSd = GetSymbolData(std::to_string(ctxInfo.Vars[i]));
            // Заполняем сдвиг у переменной
            tempSd.Offset = (ctxInfo.Len - i - 1) * 2;
        }
    }

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable)
    {
        size_t codeLen = 4;
        size_t nameLen = 4;
        size_t kindLen = 4;
        size_t typeLen = 4;
        size_t lenLen = 3;
        size_t initLen = 4;
        size_t offsetLen = 6;
        size_t scopeLen = 5;
        size_t temp = 0;

        std::string coll = "│ ";
        std::string colr = " │";
        std::string col = " │ ";

        auto prepareData = [=](int len, std::string data, std::string orient = "left")
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
            temp = std::to_string(code).length();
            codeLen = temp > codeLen ? temp : codeLen;

            temp = sd.Name.length();
            nameLen = temp > nameLen ? temp : nameLen;

            temp = std::to_string(int(sd.Kind)).length();
            kindLen = temp > kindLen ? temp : kindLen;

            temp = std::to_string(int(sd.Type)).length();
            typeLen = temp > typeLen ? temp : typeLen;

            temp = sd.Len.length();
            lenLen = temp > lenLen ? temp : lenLen;

            temp = sd.Init.length();
            initLen = temp > initLen ? temp : initLen;

            temp = std::to_string(sd.Offset).length();
            offsetLen = temp > offsetLen ? temp : offsetLen;

            temp = std::to_string(sd.Scope).length();
            scopeLen = temp > scopeLen ? temp : scopeLen;
        }

        std::stringstream sep;
        sep << "├" << fill(codeLen + 2) << "┼" << fill(nameLen + 2) << "┼" << fill(scopeLen + 2) << "┼" << fill(kindLen + 2) << "┼" << fill(typeLen + 2) << "┼" << fill(lenLen + 2) << "┼" << fill(initLen + 2) << "┼" << fill(offsetLen + 2) << "┤" << std::endl;

        std::stringstream top;
        top << "┌" << fill(codeLen + 2) << "┬" << fill(nameLen + 2) << "┬" << fill(scopeLen + 2) << "┬" << fill(kindLen + 2) << "┬" << fill(typeLen + 2) << "┬" << fill(lenLen + 2) << "┬" << fill(initLen + 2) << "┬" << fill(offsetLen + 2) << "┐" << std::endl;

        std::stringstream bottom;
        bottom << "└" << fill(codeLen + 2) << "┴" << fill(nameLen + 2) << "┴" << fill(scopeLen + 2) << "┴" << fill(kindLen + 2) << "┴" << fill(typeLen + 2) << "┴" << fill(lenLen + 2) << "┴" << fill(initLen + 2) << "┴" << fill(offsetLen + 2) << "┘" << std::endl;

        os << top.str();
        os << coll << prepareData(codeLen, "Code") << col << prepareData(nameLen, "Name") << col << prepareData(scopeLen, "Scope") << col << prepareData(kindLen, "Kind") << col << prepareData(typeLen, "Type") << col << prepareData(lenLen, "Len") << col << prepareData(initLen, "Init") << col << prepareData(offsetLen, "Offset") << colr << std::endl;
        os << sep.str();

        for (auto [code, sd] : symtable.data)
        {
            os << coll << prepareData(codeLen, std::to_string(code), "right") << col << prepareData(nameLen, sd.Name) << col << prepareData(scopeLen, std::to_string(sd.Scope), "right") << col << prepareData(kindLen, sd.GetKind()) << col << prepareData(typeLen, sd.GetType()) << col << prepareData(lenLen, sd.Len) << col << prepareData(initLen, sd.Init, "right") << col << prepareData(offsetLen, std::to_string(sd.Offset), "right") << colr << std::endl;
        }

        os << bottom.str();

        return os;
    }
}