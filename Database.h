//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H
#include <map>
#include <string>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation>  myRelations;

public:
    void AddRelation(Relation newRelation) {
        myRelations.insert({newRelation.GetName(),newRelation});
    }

    Relation* GetRelation(std::string relationName) {
        return &myRelations.at(relationName);
    }

    Relation GetRelationCopy(std::string relationName) {
        return myRelations.at(relationName);
    };

    void DoUnion (Relation interRelation, Relation originRelation) {
        myRelations.at(interRelation.GetName()) = interRelation.unionize(interRelation, originRelation);
    }

    int count() {
        int counter = 0;
        for (std::pair<std::string, Relation> numRelations : myRelations) {
            counter += numRelations.second.GetTuples().size();
        }
        //std::cout<< "this is my number of tuples in the relation = " << counter << std::endl;
        return counter;
    }
};


#endif //PROJECT_1_DATABASE_H
