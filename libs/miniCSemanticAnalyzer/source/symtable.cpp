#include <miniCSemanticAnalyzer/symtable.h>

namespace miniCSemanticAnalyzer
{
    SymbolTable::SymbolTable(){};

    SymbolData &SymbolTable::GetSymbolData(int code)
    {
        return data[code];
    }

    std::pair<int, bool> SymbolTable::findSymbolData(std::string name)
    {
        for (size_t i = contextArray.size() - 1; i >= 0; i--)
        {
            auto [code, ok] = subData[i][name];
            if (ok)
            {
                return {code, ok};
            }
        }

        return {NULL, false};
    }

    int SymbolTable::Alloc()
    {
        SymbolData temp{
            "#DEV_" + std::to_string(currentCode),
            SymbolClass::Dev,
            SymbolType::Dev,
            NULL,
            NULL};

        data[currentCode] = temp;
        return currentCode++;
    }

    void SymbolTable::EnterContext()
    {
        contextArray.push_back(currentContext++);
    }

    void SymbolTable::ExitContext()
    {
        contextArray.pop_back();
    }

    int SymbolTable::NewLabel()
    {
        return currentLabel++;
    }

    std::pair<int, bool> SymbolTable::CheckVar(std::string name)
    {
        auto [code, ok] = findSymbolData(name);
        if (ok)
        {
            return {code, ok};
        }
        return {NULL, false};
    }

    int SymbolTable::AddVar(std::string name, SymbolType type, int init)
    {
        SymbolData temp{
            name,
            SymbolClass::Var,
            type,
            NULL,
            init};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return currentCode++;
    }

    std::pair<int, bool> SymbolTable::CheckFunc(std::string name, unsigned int len)
    {
        auto [code, ok] = findSymbolData(name + "_" + std::to_string(len));
        if (ok)
        {
            return {code, ok};
        }
        return {NULL, false};
    }

    int SymbolTable::AddFunc(std::string name, SymbolType type, unsigned int len)
    {
        SymbolData temp{
            name + std::to_string(len),
            SymbolClass::Func,
            type,
            len,
            NULL};

        subData[contextArray.back()][temp.Name] = {currentCode, true};
        data[currentCode] = temp;

        return currentCode++;
    }
}