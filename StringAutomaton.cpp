//
// Created by Juan on 9/20/2022.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index]=='\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index>=static_cast<int>(input.size())) {
        type = TokenType::UNDEFINED;
    }

    /*else if (input[index]==EOF) {
        type = TokenType::UNDEFINED;
    }*/

    else if (input[index]=='\n') {
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }

    else if (input[index]=='\'') {
        inputRead++;
        index++;
        S3(input);
    }

    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (index>=static_cast<int>(input.size())) {
        type = TokenType::UNDEFINED;
    }

    /*else if (input[index]==EOF) {
        type = TokenType::UNDEFINED;
    }*/

    else if (input[index]=='\n') {
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }

    else if (input[index]=='\'') {
        inputRead++;
        index++;
        S3(input);
    }

    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void StringAutomaton::S3(const std::string &input) {
    if (input[index]=='\'') {
        inputRead++;
        index++;
        S2(input);
    }
}