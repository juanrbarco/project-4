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

    void PrintRelations() {
        interpretSchemes();
        interpretFacts();
        interpretQueries();
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

};


#endif //PROJECT_1_INTERPRETER_H
