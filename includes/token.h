#pragma once
#include <string>

enum class LexemTypes {
    num,
    chr,
    str,
    id,
    lpar,
    rpar,
    lbrace,
    rbrace,
    lbracket,
    rbracket,
    semicolon,
    comma,
    colon,
    opassign,
    opplus,
    opminus,
    opmult,
    opinc,
    opeq,
    opne,
    oplt,
    opgt,
    ople,
    opnot,
    opor,
    opand,
    kwint,
    kwchar,
    kwif,
    kwelse,
    kwswitch,
    kwcase,
    kwwhile,
    kwfor,
    kwreturn,
    kwin,
    kwout,
    eof,
};

using ll = long long;

class Token
{
    private:
        int type;
        ll num;
        std::string str;
    public:
        Token(int type);
        Token(int type, ll num);
        Token(int type, std::string str);
        int type();
        int value();
        std::string getLexem();
};