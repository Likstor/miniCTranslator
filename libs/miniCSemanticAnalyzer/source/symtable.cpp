#include <miniCSemanticAnalyzer/symtable.h>

namespace miniCSemanticAnalyzer
{
    SymbolTable::SymbolTable(){};

    SymbolData &SymbolTable::getSymbolData(int context, std::string name)
    {
        return data[context][name];
    }

    std::pair<int, bool> SymbolTable::findSymbolData(std::string name)
    {
        for (size_t i = contextArray.size() - 1; i >= 0; i--)
        {
            if (contextMap[name][i] == true)
            {
                return {i, true};
            }
        }

        return {0, false};
    }

    int Alloc()
    {
    }

    int EnterContext()
    {
    }

    int ExitContext()
    {
    }

    int NewLabel()
    {
    }

    int CheckVar(std::string name)
    {
    }

    int AddVar(std::string name, std::string type, std::string init)
    {
    }

    int CheckFunc(std::string name, int len)
    {
    }

    int AddFunc(std::string name, std::string type)
    {
    }
}