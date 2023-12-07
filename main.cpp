#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <lexer.h>

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

std::unordered_map<ll, edgesMap> lexicalGraph = {
    {0, {
            {" ", {0, true, false, ""}},
            {"\n", {0, true, false, ""}},
            {"\'", {11, true, false, ""}},
            {"\"", {13, true, false, ""}},
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
        }},
    {2, {{"=", {0, true, false, "ople"}}, {"default", {0, false, false, "oplt"}}}},
    {3, {{"=", {0, true, false, "opne"}}, {"default", {0, false, false, "opnot"}}}},
    {4, {{"=", {0, true, false, "opeq"}}, {"default", {0, false, false, "opassign"}}}},
    {5, {{"+", {0, true, false, "opinc"}}, {"default", {0, false, false, "opplus"}}}},
    {6, {// or
         {"|", {0, true, false, "opor"}},
         {"default", {-1, false, false, "error"}}}},
    {7, {// and
         {"&", {0, true, false, "opand"}},
         {"default", {-1, false, false, "error"}}}},
    {8, {// int
         {"digit", {8, true, true, ""}},
         {"default", {0, false, false, "num"}}}},
    {9, {{"digit", {8, true, true, ""}}, {"default", {0, false, false, "clear|opminus"}}}},
    {10, {{"letter", {10, true, true, ""}}, {"digit", {10, true, true, ""}}, {"default", {0, false, false, "id"}}}},
    {11, {// char
          {"\'", {-1, false, false, "error"}},
          {"default", {12, true, true, ""}}}},
    {12, {{"\'", {0, true, false, "chr"}}, {"default", {-1, false, false, "error"}}}},
    {13, {// str
          {"\"", {0, true, false, "str"}},
          {"eof", {-1, false, false, "error"}},
          {"default", {13, true, true, ""}}}}};

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "None file path";
        return -1;
    }

    Lexer lexer(argv[1], lexicalGraph, keywords);

    for (int i = 0; i != -1; i++)
    {
        Token temp = lexer.getNextLexem();

        std::cout << "[" << temp.token << ", \"" << temp.value << "\"]" << std::endl;

        if (temp.token == "error" || temp.token == "eof")
        {
            break;
        }
    }
}