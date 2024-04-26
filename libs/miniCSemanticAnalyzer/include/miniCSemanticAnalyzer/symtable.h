#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

namespace miniCSemanticAnalyzer
{
    struct SymbolData
    {
        std::string Class;
        std::string Type;
        int Len;
    };

    class SymbolTable
    {
    private:
        std::unordered_map<int, std::unordered_map<std::string, SymbolData>> data;
        std::unordered_map<std::string, std::unordered_map<int, bool>> contextMap;

        std::vector<int> contextArray = {-1};
        int currentCode = 0;
        int currentContext = -1;
        int currentLabel = 0;

        SymbolData &getSymbolData(int context, std::string name);
        std::pair<int, bool> findSymbolData(std::string name);

    public:
        SymbolTable();

        int Alloc();

        int EnterContext();
        int ExitContext();

        int NewLabel();

        int CheckVar(std::string name);
        int AddVar(std::string name, std::string type, std::string init);

        int CheckFunc(std::string name, int len);
        int AddFunc(std::string name, std::string type);
    };

    std::ostream &operator<<(std::ostream &os, const SymbolTable &symtable);
}