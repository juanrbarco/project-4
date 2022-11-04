//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include<string>
#include<set>
#include<iostream>
#include"Header.h"
#include"Tuple.h"

class Relation {
private:
    std::string name;
    Header header;
    std::set<Tuple> rows;
public:
    Relation() = default;
    Relation(std::string name, Header header) {
        this->name = name;
        this->header = header;
    }
    Relation(std::string name, Header header, std::set<Tuple> rows) {
        this->name = name;
        this->header = header;
        this->rows = rows;
    }

    void AddName(std::string name) {
        this->name = name;
    }

    void AddHeader(Header header) {
        this->header = header;
    }

    void AddTuple(Tuple newTuple) {
        rows.insert(newTuple);
    }
    std::string GetName() {
        return name;
    }

    Relation Select(int index, std::string value){
        Relation newRelation(name, header);
        for (Tuple t: rows) {
            if (value == t.toStringSingle(index)) {
                newRelation.AddTuple(t);
            }
        }
        return newRelation;
    }

    Relation Select(int index1, int index2) {
        Relation newRelation(name, header);
            for (Tuple t: rows){
                if (t.toStringSingle(index1) == t.toStringSingle(index2)) {
                    newRelation.AddTuple(t);
                }
            }
        return newRelation;
    }

    Relation Project(std::vector<int> indexes) {
        std::vector<std::string> newHeaders;

        for (int it: indexes) {
                newHeaders.push_back(header.toStringSingle(it));
        }
        Header newHeader(newHeaders);
        Relation newRelation(name, newHeader);

        for(Tuple t: rows){
            std::vector<std::string> newValues;
            for (int it : indexes) {
                newValues.push_back(t.toStringSingle(it));
            }

            Tuple newTuple(newValues);
            newRelation.AddTuple(newTuple);
        }
        return newRelation;
    }

    Relation Rename(std::vector<std::string> newNames) {
        Header newHeader(newNames);
        Relation newRelation(name, newHeader, rows);

        return newRelation;
    }

    void PrintRelation() {
        if (rows.empty()) {
            std::cout << "No" << std::endl;
        }
        else {

            std::cout << "Yes(" << rows.size() << ")" << std::endl;
        }
        //std::cout << "My headers (in relation): " << header.toString() << std::endl;
        for (Tuple t: rows) {
            for (unsigned int i =0; i < header.GetHeader().size(); i++) {
                if (i == 0 && i==(header.GetHeader().size() -1)) {
                    std::cout << "  " << header.GetHeader().at(i) << "=" << t.toStringSingle(i) << std::endl;
                }

                else if (i == (header.GetHeader().size()-1)) {
                    std::cout << header.GetHeader().at(i) << "=" << t.toStringSingle(i) << std::endl;
                }
                else if (i == 0) {
                    std::cout << "  " <<header.GetHeader().at(i) << "=" << t.toStringSingle(i) << ", ";
                }
                else {
                    std::cout << header.GetHeader().at(i) << "=" << t.toStringSingle(i) << ", ";
                }
            }
           // std::cout << "My headers (in relation)" << header.toStringSingle(index) << "= my tuples (in relation): " << t.toString() << std::endl;
        }
    }
};


#endif //PROJECT_1_RELATION_H
