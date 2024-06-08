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
        std::string Name; // Имя переменной
        int Scope; // Контекст
        SymbolKind Kind; // var or func
        SymbolType Type; // Тип переменной
        std::string Len; // Количество аргументов если это функция
        std::string Init; // Изначальное значение
        int Offset; // Сдвиг

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
        size_t Len; // Количество переменных в контексте
        std::vector<long long int> Vars; // Коды переменных
    };

    class SymbolTable
    {
    private:
        std::unordered_map<int, SymbolData> data;
        std::unordered_map<int, std::unordered_map<std::string, std::pair<int, bool>>> subData;

        std::vector<int> contextArray = {-1};
        int currentCode = 0;
        int maxContext = 0; // Максимальный номер контекста
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
        std::string AddVar(std::string name, SymbolType type, std::string init = "0");

        std::string CheckFunc(std::string name, std::string len);
        std::string AddFunc(std::string name, SymbolType type, std::string len = "0");
        friend std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);

        void AddVarToContext(int var);
        void FillOffset();
    };

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);
}
