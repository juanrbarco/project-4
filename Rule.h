//
// Created by Juan on 10/4/2022.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include <vector>
#include <string>
#include "Predicate.h"


class Rule {
public:
    //Rule(Predicate* head, Predicate* body);  TRY NO CONSTRUCTOR
    void setHead(Predicate* head);
    void setBody(Predicate* body);
    std::string toStringRule();
private:
    Predicate* head;
    std::vector<Predicate*> body;
};


#endif //PROJECT_1_RULE_H
