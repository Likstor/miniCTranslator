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

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lpar", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, rpar)
{
    std::string code = ")";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rpar", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, lbrace)
{
    std::string code = "{";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lbrace", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, rbrace)
{
    std::string code = "}";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rbrace", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, lbracket)
{
    std::string code = "[";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("lbracket", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, rbracket)
{
    std::string code = "]";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("rbracket", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, semicolon)
{
    std::string code = ";";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("semicolon", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, comma)
{
    std::string code = ",";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("comma", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, colon)
{
    std::string code = ".";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("colon", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opgt)
{
    std::string code = ">";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opgt", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opmul)
{
    std::string code = "*";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opmul", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, eof)
{
    std::string code = "";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, error)
{
    std::string code = "\\";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, space)
{
    std::string code = "     ";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, ople)
{
    std::string code = "<=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("ople", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, oplt)
{
    std::string code = "<";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("oplt", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opne)
{
    std::string code = "!=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opne", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opnot)
{
    std::string code = "!";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opnot", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opeq)
{
    std::string code = "==";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opeq", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opassign)
{
    std::string code = "=";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opassign", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opinc)
{
    std::string code = "++";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opinc", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opplus)
{
    std::string code = "+";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opplus", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opor)
{
    std::string code = "||";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opor", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, oporError)
{
    std::string code = "|";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opand)
{
    std::string code = "&&";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("opand", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, opandError)
{
    std::string code = "&";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, num)
{
    std::string code = "431441";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("num", "431441"), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, id1)
{
    std::string code = "testId123_Test";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("id", "testId123_Test"), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, id2)
{
    std::string code = "_Test";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("id", "_Test"), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, chr)
{
    std::string code = "'a'";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("chr", "a"), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, chrError)
{
    std::string code = "'";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, str)
{
    std::string code = "\"test text\"";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("str", "test text"), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, strError)
{
    std::string code = "\"test text";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("error", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwif)
{
    std::string code = "if";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwif", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwelse)
{
    std::string code = "else";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwelse", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwswitch)
{
    std::string code = "switch";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwswitch", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwcase)
{
    std::string code = "case";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwcase", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwwhile)
{
    std::string code = "while";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwwhile", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwfor)
{
    std::string code = "for";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwfor", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwreturn)
{
    std::string code = "return";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwreturn", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwin)
{
    std::string code = "in";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwin", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwout)
{
    std::string code = "out";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwout", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwint)
{
    std::string code = "int";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwint", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}

TEST(LexemeTest, kwchar)
{
    std::string code = "char";
    std::istringstream inputStream(code);

    miniCLexer::Lexer lexer{inputStream};

    EXPECT_TRUE(CheckToken(miniCLexer::Token("kwchar", ""), lexer.getNextLexem()));
    EXPECT_TRUE(CheckToken(miniCLexer::Token("eof", ""), lexer.getNextLexem()));
}