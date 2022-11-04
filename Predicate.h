//
// Created by Juan on 10/4/2022.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include <string>
#include<vector>
#include "Parameter.h"

class Predicate {
public:
    //Predicate(const std::string& id);
    void setParameters(Parameter* parameter);
    void setId(const std::string& ID);
    //std::string toStringId();
    //std::string toStringParameters();
    std::string toStringPredicate();

    std::vector<Parameter*> GetParameters(){
        return parameters;
    }

    std::string ToStringParameter(std::vector<Parameter*> readParameter) {
        std::string parameterString;

        for (unsigned int i = 0; i < readParameter.size(); i++) {
            parameterString += readParameter.at(i)->toString();
        }
        return parameterString;
    }
    std::string GetID() {
        return id;
    }



private:
    std::string id;
    std::vector<Parameter*> parameters;
};


#endif //PROJECT_1_PREDICATE_H
