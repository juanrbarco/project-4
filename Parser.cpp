//
// Created by Juan on 10/4/2022.
//

#include <iostream>
#include "Parser.h"

Parser::Parser(const std::vector<Token*>& vectorTokens) {
    for (long unsigned int i = 0; i < vectorTokens.size(); i++) {
        if (vectorTokens.at(i)->getTokenType()==TokenType::COMMENT) {}
        else {
            tokens.push_back(vectorTokens.at(i));
        }
    }
}

Parser::~Parser() {
    for (long unsigned int i = 0; i < tokens.size(); i++) {
        delete tokens.at(i);
    }
    tokens.clear();
}

void Parser::parse() {
    try {
        parserDatalogProgram();
        //std::cout <<  "Success!" << std::endl;
        //program.printProgram();
        //toStringDomain();
    }
    catch (Token* match) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  (" << tokens.at(index)->tokenTypeToString(tokens.at(index)->getTokenType()) << ",\"" << tokens.at(index)->getActualValue();
        std::cout << "\"," << tokens.at(index)->getLineNumber() << ")";
    }
}


void Parser::match(TokenType expectedToken) {
    TokenType currentToken = tokens.at(index)->getTokenType();
    if (expectedToken == currentToken) {
        index++;
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::parserDatalogProgram() {
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    parseQuery();
    parseQueryList();
    match(TokenType::EOF_TYPE);
}

void Parser::parseSchemeList() {
    if (tokens.at(index)->getTokenType()==TokenType::FACTS) {}
    else {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFactList() {
    if (tokens.at(index)->getTokenType()==TokenType::RULES) {}
    else {
        parseFact();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if (tokens.at(index)->getTokenType()==TokenType::QUERIES) {}
    else {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseQueryList() {
    if (tokens.at(index)->getTokenType()==TokenType::EOF_TYPE){}
    else {
        parseQuery();
        parseQueryList();
    }
}

void Parser::parseScheme() {
    Predicate* prediScheme = new Predicate; //creating new
    prediScheme->setId(tokens.at(index)->getActualValue()); //set its ID

    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);

    prediScheme->setParameters(new Parameter(tokens.at(index)->getActualValue())); //add this parameter

    match(TokenType::ID);
    parseIdList(prediScheme); //Look for more parameters
    match(TokenType::RIGHT_PAREN);

    program.addScheme(prediScheme);  //add Scheme to program
}

void Parser::parseFact() {
    Predicate* prediFact = new Predicate; //creating new
    prediFact->setId(tokens.at(index)->getActualValue()); //set its ID

    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);

    prediFact->setParameters(new Parameter(tokens.at(index)->getActualValue())); //set first parameter
    domain.insert(tokens.at(index)->getActualValue()); //set domain

    match(TokenType::STRING);

    parseStringList(prediFact); // Look for rest of parameters;

    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);

    program.addFacts(prediFact); //add Fact to datalog
}

void Parser::parseRule() {

    Rule* myRule = new Rule; //create new Rule
    /*Predicate* ruleBody = new Predicate; //creating new
    ruleBody->setId(tokens.at(index)->getActualValue()); //set its ID
    myPredicate = ruleBody;
    //myRule.setBody(myPredicate);*/

    parseHeadPredicate(myRule);

    //myRule.setHead(myPredicate); //set rule's head here!
    //program.addRules(myRule);

    match(TokenType::COLON_DASH);

    parsePredicate(myRule);

    //myRule.setBody(myPredicate);

    parsePredicateList(myRule);
    match(TokenType::PERIOD);

    program.addRules(myRule);
}

void Parser::parseQuery() {
    Predicate* prediQuery = new Predicate; //creating new
    prediQuery->setId(tokens.at(index)->getActualValue()); //set its ID

    parsePredicate(prediQuery);

    match(TokenType::Q_MARK);

    program.addQueries(prediQuery);
}

void Parser::parseHeadPredicate(Rule* myRule) {
    Predicate* ruleHead = new Predicate; //creating new head
    ruleHead->setId(tokens.at(index)->getActualValue()); //set its ID
    //myPredicate = ruleHead;

    //myRule->setHead(myPredicate);

    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);

    //myParameter = new Parameter(tokens.at(index)->getActualValue());
    //myPredicate->setParameters(myParameter);
    ruleHead->setParameters(new Parameter(tokens.at(index)->getActualValue())); //set first parameter

    match(TokenType::ID);

    parseIdList(ruleHead); //look for more parameters;

    match(TokenType::RIGHT_PAREN);

   // program.addRules(myRule); //add to datalog*/
    myRule->setHead(ruleHead); //add head to rule
}

void Parser::parsePredicate(Rule* myRule) {

    Predicate* ruleBody = new Predicate; // create new rule body
    ruleBody->setId(tokens.at(index)->getActualValue()); //set its ID

    /*Predicate* ruleBody = new Predicate; //creating new
    ruleBody->setId(tokens.at(index)->getActualValue()); //set its ID
    myPredicate = ruleBody;*/

    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);

    //ruleBody->setParameters(new Parameter(tokens.at(index)->getActualValue())); //set first parameter

    parseParameter(ruleBody);
    parseParameterList(ruleBody);
    match(TokenType::RIGHT_PAREN);
    myRule->setBody(ruleBody); //add to the body of rule
}



void Parser::parsePredicate(Predicate* myPredicate) {
    /*Predicate* ruleBody = new Predicate; //creating new
    ruleBody->setId(tokens.at(index)->getActualValue()); //set its ID
    myPredicate = ruleBody;*/

    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    parseParameter(myPredicate);
    parseParameterList(myPredicate);
    match(TokenType::RIGHT_PAREN);
}





void Parser::parsePredicateList(Rule* myRule) {
    if (tokens.at(index)->getTokenType()==TokenType::PERIOD) {}
    else {
        match(TokenType::COMMA);
        parsePredicate(myRule);
        parsePredicateList(myRule);
    }
}

void Parser::parseParameterList(Predicate* myPredicate) {
    if (tokens.at(index)->getTokenType()==TokenType::RIGHT_PAREN) {}
    else {
        match(TokenType::COMMA);
        parseParameter(myPredicate);
        parseParameterList(myPredicate);
    }
}

void Parser::parseStringList(Predicate* myPredicate) {
    if (tokens.at(index)->getTokenType()==TokenType::RIGHT_PAREN) {}
    else {
        match(TokenType::COMMA);

        myPredicate->setParameters(new Parameter(tokens.at(index)->getActualValue())); //set parameter for Facts
        domain.insert(tokens.at(index)->getActualValue()); //populating facts

        match(TokenType::STRING);

        parseStringList(myPredicate); // Look for more parameters
    }
}

void Parser::parseIdList(Predicate* myPredicate) {
    if (tokens.at(index)->getTokenType()==TokenType::RIGHT_PAREN) {
    }
    else {
        match(TokenType::COMMA);

        myPredicate->setParameters(new Parameter(tokens.at(index)->getActualValue()));

        match(TokenType::ID);
        parseIdList(myPredicate);
    }
}

void Parser::parseParameter(Predicate* myPredicate) {
    /*Parameter* para = new Parameter(tokens.at(index)->getActualValue());
    myParameter = para;*/
    /*myPredicate->setParameters( myParameter);*/  //first method
    myPredicate->setParameters(new Parameter(tokens.at(index)->getActualValue()));

    if (tokens.at(index)->getTokenType()==TokenType::STRING) {
        match(TokenType::STRING);

    }
    else if (tokens.at(index)->getTokenType()==TokenType::ID) {
        match(TokenType::ID);


    }
}

void Parser::toStringDomain() {
    /*std::cout <<"Domain(" <<domain.size() << "):" << std::endl;
    for (auto& str: domain) {
        std::cout <<  "  " << str <<std::endl;
    }*/
    std::cout <<"Domain(" <<domain.size() << "):" << std::endl;
    std::set<std::string>::iterator setItr = domain.begin();
    for (long unsigned int i = 0; i < domain.size(); setItr++) {
            std::cout << "  " << *setItr << std::endl;
            i++;
    }
}

