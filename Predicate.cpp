//
// Created by Juan on 10/4/2022.
//

#include <iostream>
#include "Predicate.h"
/*Predicate::Predicate(const std::string& id) {
    this->id = id;

    std::cout << "this is my schemes ID: " << id << std::endl;
}*/



void Predicate::setParameters(Parameter *parameter) {
    parameters.push_back(parameter);

    //std::cout << "Parameter in predicate: " << parameter->toString() << std::endl;
}

void Predicate::setId(const std::string& ID) {
    this->id = ID;
}

/*std::string Predicate::toStringId() {
    //std::cout << "this is id in toStringId: " << std::endl;
    return id;
}

std::string Predicate::toStringParameters() {
    std::string myString = "";

    for (int i = 0; i < parameters.size(); i++) {
        if (i != (parameters.size() - 1)) {
            myString += parameters.at(i)->toString() + ",";
        }
        else {
            myString += parameters.at(i)->toString()  + ")";
        }
    }
    return myString;
}*/



std::string Predicate::toStringPredicate() {
    std::string myString = "";
    myString += id + "(";

    for (long unsigned int i = 0; i < parameters.size(); i++) {
        if (i != (parameters.size() - 1)) {
            myString += parameters.at(i)->toString() + ",";
        }
        else {
            myString += parameters.at(i)->toString()  + ")";
        }
    }
    return myString;
}