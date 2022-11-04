//
// Created by Juan on 9/20/2022.
//

#include "EOFAutomaton.h"

void EOFAutomaton::S0(const std::string& input) {
    if (input[index]==EOF) {
        inputRead++;
    }

    else {
         Serr();
    }
}