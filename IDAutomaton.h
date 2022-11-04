//
// Created by Juan on 9/20/2022.
//

#ifndef PROJECT_1_IDAUTOMATON_H
#define PROJECT_1_IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton : public Automaton {
private:
    void S1(const std::string&  input);


public:
    IDAutomaton() : Automaton(TokenType::ID) {} //Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_IDAUTOMATON_H
