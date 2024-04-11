#include <gtest/gtest.h>
#include <miniCLexer/lexer.h>
#include <vector>
#include <string>
#include <iostream>

TEST(CorrectCode, BasicProgram)
{

    std::string prog = R"(
int main() {
    return 0;
}
)";
    std::vector<miniCLexer::Token> correct = {
        {"kwint", ""},
        {"id", "main"},
        {"lpar", ""},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwreturn", ""},
        {"num", "0"},
        {"semicolon", ""},
        {"rbrace", ""},
        {"eof", ""}};

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(CorrectCode, ComplexProgram)
{

    std::string prog = R"(
int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n-2);
}

int is_even(int x) {
    while (x > 0) x = x - 2;
    return x == 0;
}

int main() {
    int n;
    in n;
    for (int i = 0; i < n; i++) {
        if (is_even(i)) {
            out fib(i);
        }
    }
    return 0;
}
)";
    std::vector<miniCLexer::Token> correct = {
        // int fib(int n) {
        {"kwint", ""},
        {"id", "fib"},
        {"lpar", ""},
        {"kwint", ""},
        {"id", "n"},
        {"rpar", ""},
        {"lbrace", ""},

        // if (n < 2) return n;
        {"kwif", ""},
        {"lpar", ""},
        {"id", "n"},
        {"oplt", ""},
        {"num", "2"},
        {"rpar", ""},
        {"kwreturn", ""},
        {"id", "n"},
        {"semicolon", ""},

        // return fib(n - 1)
        {"kwreturn", ""},
        {"id", "fib"},
        {"lpar", ""},
        {"id", "n"},
        {"opminus", ""},
        {"num", "1"},
        {"rpar", ""},

        //  + fib(n-2);
        {"opplus", ""},
        {"id", "fib"},
        {"lpar", ""},
        {"id", "n"},
        {"num", "-2"},
        {"rpar", ""},
        {"semicolon", ""},

        // }
        {"rbrace", ""},

        // int is_even(int x) {
        {"kwint", ""},
        {"id", "is_even"},
        {"lpar", ""},
        {"kwint", ""},
        {"id", "x"},
        {"rpar", ""},
        {"lbrace", ""},

        // while (x > 0)
        {"kwwhile", ""},
        {"lpar", ""},
        {"id", "x"},
        {"opgt", ""},
        {"num", "0"},
        {"rpar", ""},

        // x = x - 2;
        {"id", "x"},
        {"opassign", ""},
        {"id", "x"},
        {"opminus", ""},
        {"num", "2"},
        {"semicolon", ""},

        //    return x == 0;
        {"kwreturn", ""},
        {"id", "x"},
        {"opeq", ""},
        {"num", "0"},
        {"semicolon", ""},

        //}
        {"rbrace", ""},
        // int main() {
        {"kwint", ""},
        {"id", "main"},
        {"lpar", ""},
        {"rpar", ""},
        {"lbrace", ""},

        //    int n;
        {"kwint", ""},
        {"id", "n"},
        {"semicolon", ""},

        //    in n;
        {"kwin", ""},
        {"id", "n"},
        {"semicolon", ""},

        //    for (int i = 0;
        {"kwfor", ""},
        {"lpar", ""},
        {"kwint", ""},
        {"id", "i"},
        {"opassign", ""},
        {"num", "0"},
        {"semicolon", ""},

        //  i < n; i++) {
        {"id", "i"},
        {"oplt", ""},
        {"id", "n"},
        {"semicolon", ""},

        {"id", "i"},
        {"opinc", ""},
        {"rpar", ""},
        {"lbrace", ""},

        //        if (is_even(i)) {
        {"kwif", ""},
        {"lpar", ""},
        {"id", "is_even"},
        {"lpar", ""},
        {"id", "i"},
        {"rpar", ""},
        {"rpar", ""},
        {"lbrace", ""},

        //            out fib(i);
        {"kwout", ""},
        {"id", "fib"},
        {"lpar", ""},
        {"id", "i"},
        {"rpar", ""},
        {"semicolon", ""},

        //        }
        {"rbrace", ""},
        //    }
        {"rbrace", ""},

        //    return 0;
        {"kwreturn", ""},
        {"num", "0"},
        {"semicolon", ""},

        //}
        {"rbrace", ""},
        {"eof", ""}};

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (int i = 0; i < correct.size(); ++i)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == correct[i].LexemeType && tmp.Value == correct[i].Value) << "token #" << i;
    }
}

TEST(TrickyCode, BasicProgram)
{

    std::string prog = "int main(){return 0;}";
    std::vector<miniCLexer::Token> correct = {
        {"kwint", ""},
        {"id", "main"},
        {"lpar", ""},
        {"rpar", ""},
        {"lbrace", ""},
        {"kwreturn", ""},
        {"num", "0"},
        {"semicolon", ""},
        {"rbrace", ""},
        {"eof", ""}};

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(TrickyCode, MultilineString)
{

    std::string prog = R"(out "Hello
world
'
for everyone!!!
")";
    std::string content = "Hello\n"
                          "world\n"
                          "'\n"
                          "for everyone!!!\n";
    std::vector<miniCLexer::Token> correct = {
        {"kwout", ""},
        {"str", content},
        {"eof", ""}};

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(TrickyCode, Expressions)
{

    std::string prog = "int a=0;int aa=182;out aa+a==-123;";
    std::vector<miniCLexer::Token> correct = {
        // int a=0;
        {"kwint", ""},
        {"id", "a"},
        {"opassign", ""},
        {"num", "0"},
        {"semicolon", ""},

        // int aa=182;
        {"kwint", ""},
        {"id", "aa"},
        {"opassign", ""},
        {"num", "182"},
        {"semicolon", ""},

        // out aa+a==-123;
        {"kwout", ""},
        {"id", "aa"},
        {"opplus", ""},
        {"id", "a"},
        {"opeq", ""},
        {"num", "-123"},
        {"semicolon", ""},
        {"eof", ""}};

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(ErrorCode, BadString)
{

    std::string prog = R"(out "incomplete string;)";
    std::vector<miniCLexer::Token> correct = {
        {"kwout", ""},
        {"error", ""},
    };

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(ErrorCode, EmptyChar)
{

    std::string prog = R"(out '')";
    std::vector<miniCLexer::Token> correct = {
        {"kwout", ""},
        {"error", ""},
    };

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(ErrorCode, DoubleChar)
{

    std::string prog = R"(out 'xy')";
    std::vector<miniCLexer::Token> correct = {
        {"kwout", ""},
        {"error", ""},
    };

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}

TEST(ErrorCode, SingleOperator)
{

    std::string prog = R"(a | b)";
    std::vector<miniCLexer::Token> correct = {
        {"id", "a"},
        {"error", ""},
    };

    std::stringstream stream{prog};
    miniCLexer::Lexer lexer(stream);

    for (auto &&lex : correct)
    {
        miniCLexer::Token tmp = lexer.getNextToken();
        ASSERT_TRUE(tmp.LexemeType == lex.LexemeType && tmp.Value == lex.Value);
    }
}