//
// Created by Juan on 10/4/2022.
//

#include <iostream>
#include "Parameter.h"

Parameter::Parameter(const std::string& string) {
    this->string = string;
    //std::cout << "this is my parameter: " << string << std::endl;
}

std::string Parameter::toString() {
    return string;
}

/*void Parameter::setString(const std::string& string) {
    this->string = string;
}*/