#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

namespace miniCLexer
{

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
        ll currentState = 0;
        std::string subCache;
        std::istream &stream;

        std::unordered_map<std::string, std::string> keywords{
            {"if", "kwif"},
            {"else", "kwelse"},
            {"switch", "kwswitch"},
            {"case", "kwcase"},
            {"while", "kwwhile"},
            {"for", "kwfor"},
            {"return", "kwreturn"},
            {"in", "kwin"},
            {"out", "kwout"},
            {"char", "kwchar"},
            {"int", "kwint"},
        };

        std::unordered_map<ll, edgesMap> lexicalGraph{
            {0, {
                    {" ", {0, true, false, ""}},
                    {"\n", {0, true, false, ""}},
                    {"'", {10, true, false, ""}},
                    {"\"", {12, true, false, ""}},
                    {"<", {1, true, false, ""}},
                    {"!", {2, true, false, ""}},
                    {"=", {3, true, false, ""}},
                    {"+", {4, true, false, ""}},
                    {"(", {0, true, false, "lpar"}},
                    {")", {0, true, false, "rpar"}},
                    {"{", {0, true, false, "lbrace"}},
                    {"}", {0, true, false, "rbrace"}},
                    {"[", {0, true, false, "lbracket"}},
                    {"]", {0, true, false, "rbracket"}},
                    {";", {0, true, false, "semicolon"}},
                    {",", {0, true, false, "comma"}},
                    {".", {0, true, false, "colon"}},
                    {">", {0, true, false, "opgt"}},
                    {"*", {0, true, false, "opmul"}},
                    {"|", {5, true, false, ""}},
                    {"&", {6, true, false, ""}},
                    {"-", {8, true, true, ""}},
                    {"digit", {7, true, true, ""}},
                    {"letter", {9, true, true, ""}},
                    {"_", {9, true, true, ""}},
                    {"eof", {-1, false, false, "eof"}},
                    {"default", {-1, true, false, "error"}},
                }},
            {1, {
                    {"=", {0, true, false, "ople"}},
                    {"default", {0, false, false, "oplt"}},
                }},
            {2, {
                    {"=", {0, true, false, "opne"}},
                    {"default", {0, false, false, "opnot"}},
                }},
            {3, {
                    {"=", {0, true, false, "opeq"}},
                    {"default", {0, false, false, "opassign"}},
                }},
            {4, {
                    {"+", {0, true, false, "opinc"}},
                    {"default", {0, false, false, "opplus"}},
                }},
            {5, {
                    {"|", {0, true, false, "opor"}},
                    {"default", {-1, false, false, "error"}},
                }},
            {6, {
                    {"&", {0, true, false, "opand"}},
                    {"default", {-1, false, false, "error"}},
                }},
            {7, {
                    {"digit", {7, true, true, ""}},
                    {"default", {0, false, false, "num"}},
                }},
            {8, {
                    {"digit", {7, true, true, ""}},
                    {"default", {0, false, false, "clear|opminus"}},
                }},
            {9, {
                    {"letter", {9, true, true, ""}},
                    {"digit", {9, true, true, ""}},
                    {"_", {9, true, true, ""}},
                    {"default", {0, false, false, "id"}},
                }},
            {10, {
                    {"'", {-1, false, false, "error"}},
                    {"default", {11, true, true, ""}},
                }},
            {11, {
                    {"'", {0, true, false, "chr"}},
                    {"default", {-1, false, false, "error"}},
                }},
            {12, {
                    {"\"", {0, true, false, "str"}},
                    {"eof", {-1, false, false, "error"}},
                    {"default", {12, true, true, ""}},
                }},
        };

        void read();
        void append();
        void runCommand(std::string command, edge currentEdge);

        Token createToken(std::string lexem, std::string value);

    public:
        Lexer(std::istream &stream);
        Token getNextLexem();
    };
}