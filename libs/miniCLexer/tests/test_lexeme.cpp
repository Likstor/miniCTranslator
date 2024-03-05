#include <gtest/gtest.h>
#include <miniCLexer/lexer.h>
#include <string>
#include <iostream>

::testing::AssertionResult CheckToken(miniCLexer::Token ltoken, miniCLexer::Token rtoken)
{
    if (ltoken.token == rtoken.token && ltoken.value == rtoken.value)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << rtoken.token << rtoken.value;
}

TEST(LexemeTest, lpar)
{
    std::string code = "(";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lpar", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, rpar)
{
    std::string code = ")";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rpar", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, lbrace)
{
    std::string code = "{";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lbrace", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, rbrace)
{
    std::string code = "}";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rbrace", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, lbracket)
{
    std::string code = "[";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lbracket", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, rbracket)
{
    std::string code = "]";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rbracket", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, semicolon)
{
    std::string code = ";";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("semicolon", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, comma)
{
    std::string code = ",";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("comma", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, colon)
{
    std::string code = ".";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("colon", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opgt)
{
    std::string code = ">";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opgt", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opmul)
{
    std::string code = "*";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opmul", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, eof)
{
    std::string code = "";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, error)
{
    std::string code = "\\";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, space)
{
    std::string code = "     ";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, ople)
{
    std::string code = "<=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("ople", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, oplt)
{
    std::string code = "<";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("oplt", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opne)
{
    std::string code = "!=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opne", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opnot)
{
    std::string code = "!";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opnot", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opeq)
{
    std::string code = "==";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opeq", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opassign)
{
    std::string code = "=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opassign", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opinc)
{
    std::string code = "++";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opinc", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opplus)
{
    std::string code = "+";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opplus", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opor)
{
    std::string code = "||";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opor", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, oporError)
{
    std::string code = "|";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opand)
{
    std::string code = "&&";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opand", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, opandError)
{
    std::string code = "&";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, num)
{
    std::string code = "431441";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("num", "431441"), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, id1)
{
    std::string code = "testId123_Test";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("id", "testId123_Test"), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, id2)
{
    std::string code = "_Test";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("id", "_Test"), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, chr)
{
    std::string code = "'a'";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("chr", "a"), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, chrError)
{
    std::string code = "'";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, str)
{
    std::string code = "\"test text\"";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("str", "test text"), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, strError)
{
    std::string code = "\"test text";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwif)
{
    std::string code = "if";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwif", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwelse)
{
    std::string code = "else";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwelse", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwswitch)
{
    std::string code = "switch";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwswitch", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwcase)
{
    std::string code = "case";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwcase", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwwhile)
{
    std::string code = "while";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwwhile", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwfor)
{
    std::string code = "for";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwfor", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwreturn)
{
    std::string code = "return";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwreturn", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwin)
{
    std::string code = "in";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwin", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwout)
{
    std::string code = "out";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwout", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwint)
{
    std::string code = "int";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwint", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}

TEST(LexemeTest, kwchar)
{
    std::string code = "char";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwchar", ""), lexer.getNextToken()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextToken()));
}