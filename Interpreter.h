//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include<vector>
#include"Database.h"
#include"DatalogProgram.h"
#include<list>

class Interpreter {
private:
    int counter = 0;
    std::set<std::string> allMyRules;
    DatalogProgram program;
    Database database;
    Database answeredQueries;

public:
    Interpreter(DatalogProgram program) {
        this->program = program;
    }

    void interpretSchemes() {
        std::vector<Predicate*> mySchemes = program.GetSchemes();
        for (unsigned int i = 0; i < mySchemes.size(); i++) {
            Relation* myRelation = new Relation;
                //Relation(mySchemes.at(i)->GetID());
                //std::string myHeaders;
                //std::vector<std::string> myHeaderString;
                Header myHeaderString;
                //std::vector<Parameter*> myHeaders =  mySchemes.at(i)->GetParameters();
                //for (int j = 0; j <myHeaders.size(); j++) {
                //std::cout << "My table name: " << mySchemes.at(i)->GetID() << std::endl;  //Print Table Names!
                for (unsigned int j = 0; j < mySchemes.at(i)->GetParameters().size(); j++) {
                    //myHeaderString->setAttributes(myHeaders.at(j)->toString());
                    myHeaderString.setAttributes(mySchemes.at(i)->GetParameters().at(j)->toString());

                    //std::cout << "My Headers: " << mySchemes.at(i)->GetParameters().at(j)->toString() << std::endl; //Print Headers!
                }
                myRelation->AddName(mySchemes.at(i)->GetID());
                myRelation->AddHeader(myHeaderString);
                database.AddRelation(*myRelation);
                delete myRelation;
            //database.AddRelation(Relation(mySchemes.at(i)->GetID(), myHeaderString));
        }
    }

    void interpretFacts() {
        std::vector<Predicate*> myFacts = program.GetFacts();
        for (unsigned int i = 0; i < myFacts.size(); i++) {
            //database.GetRelation(myFacts.at(i)->GetID());
            Tuple* myTuple = new Tuple;
            for (unsigned int j = 0; j < myFacts.at(i)->GetParameters().size(); j++) {
                myTuple->SetTuple(myFacts.at(i)->GetParameters().at(j)->toString());
                //std::cout << "My facts: " << myFacts.at(i)->GetParameters().at(j)->toString() << std::endl; //Print Tuples!
            }
            database.GetRelation(myFacts.at(i)->GetID())->AddTuple(*myTuple);
            //database.GetRelation(myFacts.at(i)->GetID())->PrintRelation();
            delete myTuple;
        }
    }

    void interpretQueries() {
        std::vector<Predicate*> myQueries =  program.GetQueries();
        for (unsigned int i = 0; i < myQueries.size(); i++) {

            Relation myRelation = database.GetRelationCopy(myQueries.at(i)->GetID());
            std::vector<Parameter*> myParameters = myQueries.at(i)->GetParameters();
            std::map<std::string, int> parameterMap;
            std::vector<int> projectIndexes;
            std::vector<std::string> renameAttributes;


            for (unsigned int j = 0; j < myParameters.size(); j++) {
                if (!myParameters.at(j)->IsID()) { //if it's a constant
                    myRelation = myRelation.Select(j, myParameters.at(j)->toString());
                }
                else{ //if it's variable
                    if (parameterMap.find(myParameters.at(j)->toString()) != parameterMap.end()) { //ID found
                        myRelation = myRelation.Select(j, parameterMap.at(myParameters.at(j)->toString()));
                    }
                    else { //ID not found
                        parameterMap.insert({myParameters.at(j)->toString(), j});
                        projectIndexes.push_back(j);
                        renameAttributes.push_back(myParameters.at(j)->toString());
                    }
                }
            }

            myRelation = myRelation.Project(projectIndexes);
            myRelation = myRelation.Rename(renameAttributes);

            //program.GetQueries().at(i)->PrintQueries();
            program.PrintQueries(i);
            myRelation.PrintRelation();
        }
    }

    Relation makeBodyRelations(Predicate* ruleBody) {
            Relation myRelation = database.GetRelationCopy(ruleBody->GetID());
            std::vector<Parameter*> myParameters = ruleBody->GetParameters();
            std::map<std::string, int> parameterMap;
            std::vector<int> projectIndexes;
            std::vector<std::string> renameAttributes;


            for (unsigned int j = 0; j < myParameters.size(); j++) {
                if (!myParameters.at(j)->IsID()) { //if it's a constant
                    myRelation = myRelation.Select(j, myParameters.at(j)->toString());
                }
                else{ //if it's variable
                    if (parameterMap.find(myParameters.at(j)->toString()) != parameterMap.end()) { //ID found
                        myRelation = myRelation.Select(j, parameterMap.at(myParameters.at(j)->toString()));
                    }
                    else { //ID not found
                        parameterMap.insert({myParameters.at(j)->toString(), j});
                        projectIndexes.push_back(j);
                        renameAttributes.push_back(myParameters.at(j)->toString());
                    }
                }
            }
            myRelation = myRelation.Project(projectIndexes);
            myRelation = myRelation.Rename(renameAttributes);
            return myRelation;
    }

    std::string interpretRules() {
        counter++;
        std::string myRules;
        std::vector<Rule *> ruleList = program.GetRules();

            for (int i = 0; i < ruleList.size(); i++) {
                myRules += ruleList.at(i)->toStringRule() + ".\n";

                int tupleCount = database.count();

                std::vector<Relation> intermediateRelations;
                for (int j = 0; j < ruleList.at(i)->GetBody().size(); j++) {
                    intermediateRelations.push_back(makeBodyRelations(ruleList.at(i)->GetBody().at(j)));
                }
                Relation joinedIntermediate;
                if (intermediateRelations.size() > 1) {
                    for (int k = 0; k < (intermediateRelations.size() - 1); k++) {
                        joinedIntermediate = intermediateRelations.at(k).NaturalJoin(/*intermediateRelations.at(k),*/ intermediateRelations.at(k + 1));
                        intermediateRelations.at(k + 1) = joinedIntermediate;
                    }
                } else {
                    joinedIntermediate = intermediateRelations.at(0);
                }

                Predicate *ruleHead = ruleList.at(i)->GetHead();

                joinedIntermediate.AddName(ruleHead->GetID());
                joinedIntermediate = joinedIntermediate.Project(joinedIntermediate.ProjectRule(ruleHead->GetParameters()));

                Relation databaseRelation = database.GetRelationCopy(ruleHead->GetID());

                joinedIntermediate = joinedIntermediate.Rename(databaseRelation.GetHeader().GetHeader());
                database.DoUnion(joinedIntermediate, databaseRelation);
                //  database.GetRelation(joinedIntermediate.GetName());
                //std::cout << "databaseRelation's header: " << databaseRelation.GetHeader().toString() << std::endl;
                //change = joinedIntermediate.myUnion(databaseRelation);
                database.AddRelation(joinedIntermediate);
                // std::cout << "relation in Rules: ";
                //myRules += joinedIntermediate.PrintRules();

                //myRules += ruleList.at(i)->toStringRule() + ".\n";
                allMyRules.insert(myRules);
                if(database.count() != tupleCount){
                    myRules += joinedIntermediate.toStringNew(databaseRelation) + '\n';
                    myRules = myRules.substr(0, myRules.size() - 1);
                }

            }
            //allMyRules.push_back(myRules);
            return myRules;
            //myRules.clear();

            //for (int i = 0; i < ruleList.size(); i++) {
               // myRules += ruleList.at(i)->toStringRule() + ".\n";
            //}

            //std::cout << myRules;
       // }
        //}
    }
       /*     ruleList.at(i)->GetBody();

        Relation joinedBodyRelation;
        if (bodyRelations.size() >= 2) {
            for (int i = 0; i < bodyRelations.size() - 1; i++) {
                joinedBodyRelation = bodyRelations.at(i).NaturalJoin(bodyRelations.at(i+1));
                bodyRelations.at(i+1) = joinedBodyRelation;
            }
        }
        else {
            joinedBodyRelation = bodyRelations.at(0);
        }
        joinedBodyRelation.Project();
    }*/

       void PrintRelations() {
           std::string print;
           int beforeCount = 0;
           int afterCount = 1;

           interpretSchemes();
           interpretFacts();
           std::cout << "Rule Evaluation" << std::endl;
           while (beforeCount != afterCount) {
               beforeCount = database.count();
               print += interpretRules();
               afterCount = database.count();
           }
           std::cout << print;

           std:: cout << std::endl << "Schemes populated after " << std::to_string(counter)  << " passes through the Rules." << std::endl;
           std::cout << std::endl << "Query Evaluation" << std::endl;
           interpretQueries();
       }
};


#endif //PROJECT_1_INTERPRETER_H
