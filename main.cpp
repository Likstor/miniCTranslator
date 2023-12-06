#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "miniCLexicalAnalyzer.h"

// TODO: доделать граф, обработки минуса (отрицательных чисел) и переченных/ключевых слов

std::unordered_map<std::string, std::string> keywords {
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


std::unordered_map<ll, edgesMap> lexicalGraph = {
    {0, {
        {" ", {0, true, false, ""}},
        {"\n", {0, true, false, ""}},
        {"\'", {14, true, false, ""}},
        {"\"", {18, true, false, ""}},
        {"<", {2, true, false, ""}},
        {"!", {3, true, false, ""}},
        {"=", {4, true, false, ""}},
        {"+", {5, true, false, ""}},
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
        {"|", {6, true, false, ""}},
        {"&", {7, true, false, ""}},
        {"-", {9, true, true, ""}},
        {"digit", {8, true, true, ""}},
        {"letter", {10, true, true, ""}},
        {"eof", {-1, false, false, "eof"}},
        {"default", {-1, true, false, "error"}},
        }
    },
    {2, {
        {"=", {0, true, false, "ople"}},
        {"default", {0, false, false, "oplt"}}
    }},
    {3, {
        {"=", {0, true, false, "opne"}},
        {"default", {0, false, false, "opnot"}}
    }},
    {4, {
        {"=", {0, true, false, "opeq"}},
        {"default", {0, false, false, "opassign"}}
    }},
    {5, {
        {"+", {0, true, false, "opinc"}},
        {"default", {0, false, false, "opplus"}}
    }},
    {6, { // or
        {"|", {0, true, false, "opor"}},
        {"default", {-1, false, false, "error"}}
    }},
    {7, { // and
        {"&", {0, true, false, "opand"}},
        {"default", {-1, false, false, "error"}}
    }},
    {8, { // int
        {"digit", {8, true, true, ""}},
        {"default", {0, false, false, "num"}}
    }},
    {9, {
        {"digit", {8, true, true, ""}},
        {"default", {0, false, false, "clear|opminus"}}
    }},
    {10, {
        {"letter", {10, true, true, ""}},
        {"digit", {10, true, true, ""}},
        {"default", {0, false, false, "id"}}
    }},
    {14,{ // char
        {"\'" ,{15, true, false, ""}},
        {"default", {16, true, true, ""}}
        }
    },
    {15, {
        {"default", {-1, false, false, "error"}}
        }
    },
    {16, {
        {"\'", {17, false, false, ""}}, 
        {"default", {-1, false, false, "error"}}
        }
    },
    {17, {
        {"default", {0, true, false, "chr"}}
        }
    },
    {18, { // str
        {"\"", {20, false, false, ""}},
        {"eof", {19, false, false, ""}},
        {"default", {18, true, true, ""}}
    }},
    {19, {
        {"default", {-1, false, false, "error"}}
    }},
    {20, {
        {"default", {0, true, false, "str"}},
    }}
    };

int main(int argc, char *argv[])
{
    std::ifstream file;

    if (argc == 1)
    {
        std::cerr << "None file path";
        return -1;
    }

    file.open(argv[1], std::ios::in);

    if (!file.is_open())
    {
        std::cerr << "Incorrect file path";
        return -1;
    }

    Lexer lexer(file, lexicalGraph, keywords);
}