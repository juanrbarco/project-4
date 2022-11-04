#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    int lineNumber = 1;
    int maxRead;
    int inputRead;
    Automaton* maxAutomaton;
    Token* newToken;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    std::vector<Token*> getToken() {   // use to get tokens as input for the parser
        return tokens;
    }

    void Run(std::string& input);
    void PrintTokens();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

