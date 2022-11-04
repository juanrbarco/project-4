//
// Created by Juan on 10/4/2022.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H
#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include <string>
#include <iostream>
#include<set>
//#include "Parser.h"

class DatalogProgram {
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    //std::set<Parameter> domain;
public:
    DatalogProgram() = default;
    void addScheme(Predicate *const object) {
        schemes.push_back(object);
        //std::cout << "THIS SCHEME IS IN THE DATALOG!" << std::endl;
    }

    void addFacts(Predicate *const object) {
        facts.push_back(object);
        //std::cout << "THIS PREDICATE IS IN THE DATALOG!" << std::endl;
    }

    void addQueries(Predicate *const object) {
        queries.push_back(object);
        //std::cout << "THIS QUERY IS IN THE DATALOG!" << std::endl;
    }

    void addRules(Rule* const object) {
        rules.push_back(object);
        //std::cout << "THIS RULE IS IN THE DATALOG!" << std::endl;
    }

   /* void setDomain() {
        std::set<Parameter> myDomain;

        for (int i = 0; i < facts.size(); i ++) {
            //myDomain.insert(facts.at(i)->getParameters());
        }
        domain = myDomain;
    }*/

   std::vector<Predicate*> GetSchemes() {
       return schemes;
   }

   std::vector<Predicate*> GetFacts() {
       return facts;
   }

   std::vector<Predicate*> GetQueries() {
       return queries;
   }

   void PrintQueries(int index) {
           std::cout << queries.at(index)->toStringPredicate() << "? ";
   }

    void printProgram() {
        std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
        for (long unsigned int i = 0; i < schemes.size(); i++) {
            std::cout << "  " << schemes.at(i)->toStringPredicate() << std::endl;
        }
        std::cout << "Facts(" <<facts.size() << "):" << std::endl;
        for (long unsigned int i = 0; i < facts.size(); i++) {
            std::cout <<  "  " << facts.at(i)->toStringPredicate() << "." << std::endl;
        }

       std::cout << "Rules(" <<rules.size() << "):" << std::endl;
        for (long unsigned int i = 0; i < rules.size(); i++) {
            std::cout <<  "  " << rules.at(i)->toStringRule() << "." << std::endl;
        }


        std::cout << "Queries(" <<queries.size() << "):" << std::endl;
        for (long unsigned int i = 0; i < queries.size(); i++) {
            std::cout << "  " << queries.at(i)->toStringPredicate() << "?" << std::endl;
        }

       /* std::cout <<" Domain(" <<domain.size() << "):" << std::endl;
            for (auto& str: domain) {
                std::cout << str;
            }*/
    }

    //std::string toString();
};

#endif //PROJECT_1_DATALOGPROGRAM_H