#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    // TODO: add the other types of tokens
    UNDEFINED,
    EOF_TYPE
};

class Token
{
private:
    std::string actualValue;
    int lineNumber;
    TokenType tokenType;

    //The actual value (string)
    //Line number the token starts on

    // TODO: add member variables for information needed by Token

public:
    Token(TokenType type, std::string description, int line);


    //to String Function
    std::string tokenTypeToString(const TokenType type);

    std::string getActualValue() {
        return actualValue;
    }

    int getLineNumber() const {
        return lineNumber;
    }

    TokenType getTokenType() const {
        return tokenType;
    }



    // TODO: add other needed methods
};

#endif // TOKEN_H

