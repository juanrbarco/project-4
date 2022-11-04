//
// Created by Juan on 10/4/2022.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include<vector>
#include<set>
#include"Token.h"
#include"DatalogProgram.h"
#include<iostream>

class Parser {
public:
    explicit Parser(const std::vector<Token*>& vectorTokens);
    ~Parser();
    void parse();
    void toStringDomain();
    DatalogProgram GetProgram() {
        return program;
    }

private:
    DatalogProgram program;
    std::vector<Token*> tokens;
    int index = 0;
    std::set<std::string> domain;

    void match(TokenType expectedToken);

    void parserDatalogProgram();

    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();

    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();

    void parseHeadPredicate(Rule* myRule);
    void parsePredicate(Rule* myRule);
    void parsePredicate(Predicate* myPredicate);

    void parsePredicateList(Rule* myRule);
    void parseParameterList(Predicate* myPredicate);
    void parseStringList(Predicate* myPredicate);
    void parseIdList(Predicate* myPredicate);
    void parseParameter(Predicate* myPredicate);
};


#endif //PROJECT_1_PARSER_H
