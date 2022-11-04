//
// Created by Juan on 9/20/2022.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if ((isalpha(input[index])) || (isalnum(input[index]))) {
        inputRead++;
        index++;
        S1(input);
    }

    //else {
        //inputRead++;
    //}



}
