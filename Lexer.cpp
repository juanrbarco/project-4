#include <iostream>
#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include"RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "EOFAutomaton.h"



Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {/*
    // TODO: need to clean up the memory in `automata` and `tokens`

    for (long unsigned int i = 0; i < automata.size(); i++) { //check correctness
        delete &automata.at(i);
    }
    automata.clear();

    for (long unsigned int i = 0; i <tokens.size(); i++) { //check correctness
        delete &tokens.at(i);
    }
    tokens.clear();
*/}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());


    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    lineNumber = 1;
    bool isEOF = false;
    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.at(0);

        while (std::isspace(input.at(0))) {
            if (input.at(0)=='\n') {
                lineNumber++;
            }
            input = input.substr(1, input.size());

            if (input.size() == 0) {
                isEOF = true;
                break;
            }
        }

        if (isEOF) {
            break;
        }

        for (long unsigned int i = 0; i < automata.size(); i++) {
           inputRead = automata.at(i)->Start(input);
           if (inputRead > maxRead) {
               maxRead = inputRead;
               maxAutomaton = automata.at(i);
           }
        }

        if (maxRead > 0) {
           newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
           lineNumber += maxAutomaton->NewLinesRead();
           tokens.push_back(newToken);
        }

        else {
            maxRead = 1;
             Token* undefinedToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
             tokens.push_back(undefinedToken);
        }

        input = input.substr(maxRead, input.size());
    }
    Token* newToken = new Token(TokenType::EOF_TYPE,"",lineNumber);
    tokens.push_back(newToken);

}
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {

        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */

void Lexer::PrintTokens() {
    for (long unsigned int i = 0; i < tokens.size(); i++) {

        std::cout << "(" <<tokens.at(i)->tokenTypeToString(tokens.at(i)->getTokenType()) << ",\"" << tokens.at(i)->getActualValue()
        << "\"," << tokens.at(i)->getLineNumber() <<")" << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();
}