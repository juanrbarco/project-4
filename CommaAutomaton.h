//
// Created by Juan on 9/20/2022.
//

#ifndef PROJECT_1_COMMAAUTOMATON_H
#define PROJECT_1_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {} //call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_COMMAAUTOMATON_H
