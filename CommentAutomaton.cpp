//
// Created by Juan on 9/20/2022.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] =='#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if ((index>=static_cast<int>(input.size())) || (input[index]=='\n')) {
    }

    else if (input[index]=='|') {
        inputRead++;
        index++;
        S3(input);
    }

    else if (input[index]!='|') {
        inputRead++;
        index++;
        S2(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if ((index>=static_cast<int>(input.size())) || (input[index]=='\n')) {
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string& input) {
    if (index>=static_cast<int>(input.size())) {
        type = TokenType::UNDEFINED;
    }

    else if (input[index]=='\n') {
        inputRead++;
        index++;
        newLines++;
        S3(input);
    }

    else if (input[index]!='|') {
        inputRead++;
        index++;
        S3(input);
    }

    else if (input[index]=='|') {
        inputRead++;
        index++;
        S4(input);
    }
}

void CommentAutomaton::S4(const std::string& input) {
    if (index >= static_cast<int>(input.size())) {
        type = TokenType::UNDEFINED;
    }

    else if (input[index]=='\n') {
        inputRead++;
        index++;
        newLines++;
        S3(input);
    }

    else if (input[index]=='#') {
        inputRead++;
    }

    else if (input[index]!='#') {
        inputRead++;
        index++;
        S3(input);
    }
}
