//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H
#include <vector>
#include <string>


class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple() = default;
    Tuple(std::vector<std::string> values) {
        this->values = values;
    }
    void SetTuple(std::string value) {
        values.push_back(value);
    }

    bool operator < (const Tuple &other) const {
        return values < other.values;
    }

    std::string toString() {
        std::string valuesString;
        for (unsigned int i = 0; i < values.size(); i++) {
            valuesString += values.at(i);
        }
        return valuesString;
    }

    std::string toStringSingle(int index) {
        return values.at(index);
    }



};


#endif //PROJECT_1_TUPLE_H
