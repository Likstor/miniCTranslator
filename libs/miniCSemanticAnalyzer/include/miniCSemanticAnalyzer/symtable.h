#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

namespace miniCSemanticAnalyzer
{
    enum class SymbolKind
    {
        Var,
        Func
    };

    enum class SymbolType
    {
        Char,
        Int,
        Func
    };

    struct SymbolData
    {
        std::string Name;
        int Scope;
        SymbolKind Kind;
        SymbolType Type;
        std::string Len;
        std::string Init;
        int Offset;

        std::string GetKind()
        {
            if (Kind == SymbolKind::Func)
            {
                return "Func";
            }
            else if (Kind == SymbolKind::Var)
            {
                return "Var";
            }
            else
            {
                return "Unknown";
            }
        }

        std::string GetType()
        {
            if (Type == SymbolType::Func)
            {
                return "Func";
            }
            else if (Type == SymbolType::Char)
            {
                return "Char";
            }
            else if (Type == SymbolType::Int)
            {
                return "Int";
            }
            else
            {
                return "Unknown";
            }
        }
    };

    struct Context
    {
        size_t Len;
        std::vector<long long int> Vars;
        int PrevContext;
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

        std::unordered_map<int, Context> contextMap;

        std::pair<std::string, bool> findSymbolData(std::string name);

    public:
        SymbolTable();

        int GetContext();

        std::unordered_map<int, Context> &GetContextMap();

        SymbolData &GetSymbolData(std::string code);

        std::string Alloc();

        void EnterContext();
        void ExitContext();

        std::string NewLabel();

        std::string CheckVar(std::string name);
        std::string AddVar(std::string name, SymbolType type, std::string init = "NULL");

        std::string CheckFunc(std::string name, std::string len);
        std::string AddFunc(std::string name, SymbolType type, std::string len = "0");
        friend std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);

        void AddVarToContext(int var);
        void FillOffset();
    };

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);
}