#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using ll = long long int;

struct edge
{
    ll nextState;
    bool read;
    bool append;
    std::string lexem;
};

using edgesMap = std::unordered_map<std::string, edge>;

struct Token
{
    std::string token;
    std::string value;
};

class Lexer
{
private:
    std::string cache;
    std::string buffer;
    std::unordered_map<ll, edgesMap> lexicalGraph;
    ll currentState = 0;
    std::string subCache;
    std::unordered_map<std::string, std::string> keywords;
    std::istream& stream;

    void read();
    void append();
    void runCommand(std::string command, edge currentEdge);

    Token createToken(std::string lexem, std::string value);
public:
    Lexer(std::istream &stream, const std::unordered_map<ll, edgesMap> &graph, std::unordered_map<std::string, std::string> &keywordsList);
    Token getNextLexem();
};
