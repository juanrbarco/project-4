//
// Created by Juan on 10/4/2022.
//
#include <iostream>
#include "Rule.h"
/*Rule::Rule(Predicate* head, Predicate* body) {
    this->head = head;
    this->body.push_back(body);
}*/

void Rule::setHead(Predicate* head) {
    this->head = head;
    //std::cout << "I've got a head!" << std::endl;
}

void Rule::setBody(Predicate* body) {
    this->body.push_back(body);
    //std::cout << "I've got a body!" << std::endl;
}

std::string Rule:: toStringRule() {
    std::string myString = "";

    myString += head->toStringPredicate() + " :- ";

    for (long unsigned int i= 0; i < (body.size()); i++) {
        if ((body.size() > 1) && (i != body.size()-1)) {
            myString += body.at(i)->toStringPredicate() + ",";
        }
        else {
            myString += body.at(i)->toStringPredicate();
        }
    }

    return myString;
}