//
// Created by Juan on 9/20/2022.
//

#ifndef PROJECT_1_STRINGAUTOMATON_H
#define PROJECT_1_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {} //Call to the base constructor

    void S0(const std::string& input);

};


#endif //PROJECT_1_STRINGAUTOMATON_H
