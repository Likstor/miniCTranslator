#include <gtest/gtest.h>
#include <miniCLexer/lexer.h>
#include <vector>
#include <string>
#include <iostream>

TEST(CodeBlockTest, Code1)
{
    std::string code = R"(
    int main() {
        int result = 0
        result++
        print(result)
    }
    )";

    std::vector<std::pair<std::string, std::string>> checkBox = {
        {"kwint", ""},
        {"id", "main"},
        {"lpar", ""},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwint", ""},
        {"id", "result"},
        {"opassign", ""},
        {"num", "0"},
        {"id", "result"},
        {"opinc", ""},
        {"id", "print"},
        {"lpar", ""},
        {"id", "result"},
        {"rpar", ""},
        {"rbrace", ""},
        {"eof", ""}
    };

    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    for (std::pair<std::string, std::string>& token : checkBox) {
        miniCLexer::Token tmp = lexer.getNextLexem();
        ASSERT_TRUE(token.first == tmp.token && token.second == tmp.value);
    }
}

TEST(CodeBlockTest, Code2)
{
    std::string code = R"(
    char testFunc() {
        for (int i = 0; i < 10; i++) {
            if (i * 2 == 6) {
                return '6';
            }
        }
    }
    )";

    std::vector<std::pair<std::string, std::string>> checkBox = {
        {"kwchar", ""},
        {"id", "testFunc"},
        {"lpar", ""},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwfor", ""},
        {"lpar", ""},
        {"kwint", ""},
        {"id", "i"},
        {"opassign", ""},
        {"num", "0"},
        {"semicolon", ""},
        {"id", "i"},
        {"oplt", ""},
        {"num", "10"},
        {"semicolon", ""},
        {"id", "i"},
        {"opinc", ""},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwif", ""},
        {"lpar", ""},
        {"id", "i"},
        {"opmul", ""},
        {"num", "2"},
        {"opeq", ""},
        {"num", "6"},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwreturn", ""},
        {"chr", "6"},
        {"semicolon", ""},
        {"rbrace", ""},
        {"rbrace", ""},
        {"rbrace", ""},
        {"eof", ""}
    };

    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    for (std::pair<std::string, std::string> &token : checkBox)
    {
        miniCLexer::Token tmp = lexer.getNextLexem();
        ASSERT_TRUE(token.first == tmp.token && token.second == tmp.value);
    }
}