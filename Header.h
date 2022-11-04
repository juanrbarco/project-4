//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H
#include <vector>
#include <string>


class Header {
private:
    std::vector<std::string> attributes;

public:
    Header() = default;
    Header(std::vector<std::string> attributes) {
        this->attributes = attributes;
    }



    void setAttributes(std::string const &attribute) {
        attributes.push_back(attribute);
    }

    /*std::string toStringSingle(int index) {
        return attributes.at(index);
    }*/

    std::string toString() {
        std::string headerString;
        for (unsigned int i  = 0; i < attributes.size(); i++) {
            headerString+= attributes.at(i);
        }
        return headerString;
    }

    std::vector<std::string> GetHeader() {
        return attributes;
    };

    std::string toStringSingle(int index) {
        return attributes.at(index);
    }
};


#endif //PROJECT_1_HEADER_H
