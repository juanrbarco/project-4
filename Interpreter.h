//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include<vector>
#include"Database.h"
#include"DatalogProgram.h"
#include"Graph.h"
#include<list>

class Interpreter {
private:
    int counter = 0;
    std::set<std::string> allMyRules;
    DatalogProgram program;
    Database database;
    Database answeredQueries;
    Graph forwardGraph;
    Graph reverseGraph;
    std::vector<std::set<int>> SCCList;

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

    void organizeRules() {
        std::vector<Rule*> ruleList = program.GetRules();
        std::set<int> myEdges;
        std::set<int> myReverseEdges;
        std::vector<int> nodes;

        for (unsigned int i = 0; i < ruleList.size(); i++) {
            //std::cout << "R" << i << ":" << std::endl;
            for (unsigned int j  = 0; j < ruleList.at(i)->GetBody().size(); j++) {
                unsigned int counter = 0;
                while (counter < ruleList.size()) {
                    if (ruleList.at(i)->GetBody().at(j)->GetID()==ruleList.at(counter)->GetHead()->GetID()) {
                        myEdges.insert(counter);
                    }
                    for (unsigned int k = 0; k < ruleList.at(counter)->GetBody().size(); k++) {
                        if (ruleList.at(i)->GetHead()->GetID() == ruleList.at(counter)->GetBody().at(k)->GetID()) {
                            myReverseEdges.insert(counter);
                        }
                    }
                    counter++;
                }
            }
            /*for (auto it = myEdges.begin(); it != myEdges.end(); it++ ) {
                std::cout << "the edge: " << *it << std::endl;
            }

            for (auto it = myReverseEdges.begin(); it != myReverseEdges.end(); it++ ) {
                std::cout << "the reversed edge: " << *it << std::endl;
            }*/
            forwardGraph.insertRule(i, myEdges);
            reverseGraph.insertRule(i, myReverseEdges);
            myEdges.clear();
            myReverseEdges.clear();
            //nodes.push_back(i);
        }
        forwardGraph.insertPostOrderList(reverseGraph.dfs());
        //forwardGraph.dfsForward();
        SCCList = forwardGraph.dfsForward();
    }


    std::string interpretRules2(std::vector<std::set<int>> SCCList) {
        std::vector<std::set<int>> mySCC = SCCList;
        counter++;
        std::string myRules;
        std::vector<Rule *> ruleList = program.GetRules();
        bool isSingle = true;
        std::string santaHelper;

        for (unsigned int i = 0; i < SCCList.size(); i++) {
            myRules += "SCC: ";
            for (const auto &print: SCCList.at(i)) {
                myRules += "R" + std::to_string(print) + ",";
            }
            myRules = myRules.substr(0, myRules.size()-1);
            myRules += "\n";
            if (SCCList.at(i).size() == 1) {
                auto iterator = SCCList.at(i).begin();
                int firstElement = *iterator;
                for (unsigned int l = 0; l < program.GetSingleRule(firstElement)->GetBody().size(); l ++) {
                    if (program.GetSingleRule(firstElement)->GetHead()->GetID() ==
                        program.GetSingleRule(firstElement)->GetBody().at(l)->GetID()) {
                        isSingle = false;
                        break;
                    }
                }
                if (isSingle) {
                    myRules += ruleList.at(firstElement)->toStringRule() + ".\n";

                    int tupleCount = database.count();

                    std::vector<Relation> intermediateRelations;
                    for (unsigned int j = 0; j < ruleList.at(firstElement)->GetBody().size(); j++) {
                        intermediateRelations.push_back(makeBodyRelations(ruleList.at(firstElement)->GetBody().at(j)));
                    }
                    Relation joinedIntermediate;
                    if (intermediateRelations.size() > 1) {
                        for (unsigned int k = 0; k < (intermediateRelations.size() - 1); k++) {
                            joinedIntermediate = intermediateRelations.at(k).NaturalJoin(/*intermediateRelations.at(k),*/ intermediateRelations.at(k + 1));
                            intermediateRelations.at(k + 1) = joinedIntermediate;
                        }
                    } else {
                        joinedIntermediate = intermediateRelations.at(0);
                    }

                    Predicate *ruleHead = ruleList.at(firstElement)->GetHead();

                    joinedIntermediate.AddName(ruleHead->GetID());
                    joinedIntermediate = joinedIntermediate.Project(joinedIntermediate.ProjectRule(ruleHead->GetParameters()));

                    Relation databaseRelation = database.GetRelationCopy(ruleHead->GetID());

                    joinedIntermediate = joinedIntermediate.Rename(databaseRelation.GetHeader().GetHeader());
                    database.DoUnion(joinedIntermediate, databaseRelation);
                    database.AddRelation(joinedIntermediate);
                    allMyRules.insert(myRules);
                    if(database.count() != tupleCount){
                        myRules += joinedIntermediate.toStringNew(databaseRelation) + '\n';
                        myRules = myRules.substr(0, myRules.size() - 1);
                        myRules += "1 passes: R" + std::to_string(firstElement) + "\n";
                    }
                }
            }

            if (!isSingle || (mySCC.at(i).size() > 1)) {
                int beforeCount = 0;
                int afterCount = 1;
                unsigned int counter = 0;
                while (beforeCount != afterCount) {
                    counter++;

                    beforeCount = database.count();
                    for (const auto &it: SCCList.at(i)) {

                        myRules += ruleList.at(it)->toStringRule() + ".\n";

                        int tupleCount = database.count();

                        std::vector<Relation> intermediateRelations;
                        for (unsigned int j = 0; j < ruleList.at(it)->GetBody().size(); j++) {
                            intermediateRelations.push_back(makeBodyRelations(ruleList.at(it)->GetBody().at(j)));
                        }
                        Relation joinedIntermediate;
                        if (intermediateRelations.size() > 1) {
                            for (unsigned int k = 0; k < (intermediateRelations.size() - 1); k++) {
                                joinedIntermediate = intermediateRelations.at(
                                        k).NaturalJoin(/*intermediateRelations.at(k),*/
                                        intermediateRelations.at(k + 1));
                                intermediateRelations.at(k + 1) = joinedIntermediate;
                            }
                        } else {
                            joinedIntermediate = intermediateRelations.at(0);
                        }

                        Predicate *ruleHead = ruleList.at(it)->GetHead();

                        joinedIntermediate.AddName(ruleHead->GetID());
                        joinedIntermediate = joinedIntermediate.Project(
                                joinedIntermediate.ProjectRule(ruleHead->GetParameters()));

                        Relation databaseRelation = database.GetRelationCopy(ruleHead->GetID());

                        joinedIntermediate = joinedIntermediate.Rename(databaseRelation.GetHeader().GetHeader());
                        database.DoUnion(joinedIntermediate, databaseRelation);
                        database.AddRelation(joinedIntermediate);
                        allMyRules.insert(myRules);
                        if (database.count() != tupleCount) {
                            myRules += joinedIntermediate.toStringNew(databaseRelation) + '\n';
                            myRules = myRules.substr(0, myRules.size() - 1);
                        }
                        afterCount = database.count();
                    }
                }
                myRules += std::to_string(counter) + " passes: ";
                for (const auto &helper: mySCC.at(i)) {
                    myRules += "R" + std::to_string(helper) + ",";
                }
                myRules = myRules.substr(0, myRules.size()-1);
                myRules += "\n";
                isSingle= true;
            }
        }
        return myRules;
    }


    std::string interpretRules() {

        counter++;
        std::string myRules;
        std::vector<Rule *> ruleList = program.GetRules();

            for (unsigned int i = 0; i < ruleList.size(); i++) {

                myRules += ruleList.at(i)->toStringRule() + ".\n";

                int tupleCount = database.count();

                std::vector<Relation> intermediateRelations;
                for (unsigned int j = 0; j < ruleList.at(i)->GetBody().size(); j++) {
                    intermediateRelations.push_back(makeBodyRelations(ruleList.at(i)->GetBody().at(j)));
                }
                Relation joinedIntermediate;
                if (intermediateRelations.size() > 1) {
                    for (unsigned int k = 0; k < (intermediateRelations.size() - 1); k++) {
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
           interpretSchemes();
           interpretFacts();
           std::cout << "Rule Evaluation" << std::endl;
           print += interpretRules2(SCCList);
           std::cout << print;
           std::cout << std::endl << "Query Evaluation" << std::endl;
           interpretQueries();
       }
};


#endif //PROJECT_1_INTERPRETER_H
