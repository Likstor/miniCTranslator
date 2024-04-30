#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

namespace miniCSemanticAnalyzer
{
    enum class SymbolClass
    {
        Dev,
        Var,
        Func
    };

    enum class SymbolType
    {
        Dev,
        Char,
        Func
    };

    struct SymbolData
    {
        std::string Name;
        SymbolClass Class;
        SymbolType Type;
        std::string Len;
        std::string Init;
    };

    class SymbolTable
    {
    private:
        std::unordered_map<int, SymbolData> data;
        std::unordered_map<int, std::unordered_map<std::string, std::pair<int, bool>>> subData;

        std::vector<int> contextArray = {-1};
        int currentCode = 0;
        int currentContext = -1;
        int currentLabel = 0;

        std::pair<std::string, bool> findSymbolData(std::string name);

    public:
        SymbolTable();

        SymbolData &GetSymbolData(std::string code);

        std::string Alloc();

        void EnterContext();
        void ExitContext();

        std::string NewLabel();

        std::string CheckVar(std::string name);
        std::string AddVar(std::string name, SymbolType type, std::string init);

        std::string CheckFunc(std::string name, std::string len);
        std::string AddFunc(std::string name, SymbolType type, std::string len);
    };

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);
}