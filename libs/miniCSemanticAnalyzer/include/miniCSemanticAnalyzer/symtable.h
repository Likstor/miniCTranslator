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
        unsigned int Len;
        int Init;
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

        std::pair<int, bool> findSymbolData(std::string name);

    public:
        SymbolTable();

        SymbolData &GetSymbolData(int code);

        int Alloc();

        void EnterContext();
        void ExitContext();

        int NewLabel();

        std::pair<int, bool> CheckVar(std::string name);
        int AddVar(std::string name, SymbolType type, int init);

        std::pair<int, bool> CheckFunc(std::string name, unsigned int len);
        int AddFunc(std::string name, SymbolType type, unsigned int len);
    };

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);
}