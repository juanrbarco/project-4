//
// Created by Juan on 10/21/2022.
//

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include<string>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include"Header.h"
#include"Tuple.h"
#include "Parameter.h"

class Relation {
private:
    std::string name;
    Header header;
    std::set<Tuple> rows;
    std::map<int, int> headMap;
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

    std::set<Tuple> GetTuples() {
    return rows;
    }
    Header GetHeader() {
        return header;
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

    std::vector<int> ProjectRule(std::vector<Parameter*> ruleBody) { //change the star?
        std::vector<int> matchColumns;

        for (int i = 0; i < ruleBody.size(); i++) {
            for (int j = 0; j < header.GetHeader().size(); j++) {
                if (ruleBody.at(i)->toString() == header.toStringSingle(j)) {
                    matchColumns.push_back(j);
                }
            }
        }
        return matchColumns;
    }

    Relation Rename(std::vector<std::string> newNames) {
        Header newHeader(newNames);
        Relation newRelation(name, newHeader, rows);
        return newRelation;
    }

    Header combineHeaders(std::vector<int> uniqueColumns, Header inputHeader) {
        for (int i = 0; i < uniqueColumns.size(); i++ ) {
            header.setAttributes(inputHeader.toStringSingle(uniqueColumns.at(i)));
        }
        return header;
    }

    bool IsJoinable(std::vector<std::pair<int,int>> matchColumns, Tuple firstTuple, Tuple secondTuple) {
        for (std::pair<int,int> match : matchColumns) {
            if (firstTuple.toStringSingle(match.first) != secondTuple.toStringSingle(match.second)) {
                return false;
            }
        }
        return true;
    }

    Tuple CombineTuple(std::vector<int> uniqueColumns, Tuple firstTuple, Tuple secondTuple) {
        for (int i = 0; i < uniqueColumns.size(); i++) {
            firstTuple.SetTuple(secondTuple.toStringSingle(uniqueColumns.at(i)));
            //std::cout << "My tuples at combineTuple() are: " <<firstTuple.toStringSingle(uniqueColumns.at(i)) << " & " << secondTuple.toStringSingle(uniqueColumns.at(i)) << std::endl;
        }
        //std::cout << "This is the size of my unique Columns: " << uniqueColumns.size() << std::endl;
        return firstTuple;
    }


    Relation NaturalJoin(Relation inputRelation) {
        std::vector<std::pair<int, int>> matchColumns;
        std::vector<int> uniqueColumns;
        std::vector<int> uniqueColumns1;
        headMap.clear();

        for (int i = 0; i < header.GetHeader().size(); i++) {
            bool unique = true;
            for (int j = 0; j < inputRelation.header.GetHeader().size(); j++) {
                if (header.toStringSingle(i) == inputRelation.header.toStringSingle(j)) {
                    //std::cout << "these are my headers:" << std::endl;
                    //std::cout << "origin header: " << header.toStringSingle(i) << std::endl;
                    //std::cout << "inputHeader: " << inputRelation.header.toStringSingle(j) << std::endl;

                    matchColumns.push_back(std::pair<int, int>(i, j));
                    unique = false;
                    //std::cout << i << " " << j <<std::endl;
                }
            }
        }
        for (int i = 0; i < inputRelation.header.GetHeader().size(); i++) {
            bool unique = true;
            for (int j = 0; j < matchColumns.size(); j++) {
                if (i == matchColumns.at(j).second) {
                    unique = false;
                }
            }
            if (unique) {
                uniqueColumns.push_back(i);
            }
        }
        /*for (int i = 0; i < inputRelation.header.GetHeader().size(); i++) {
            bool unique = true;
            for (int j = 0; j < matchColumns.size(); j++) {
                if (i == matchColumns.at(j).second) {
                    unique = false;
                }
            }
            if (unique) {
                uniqueColumns.push_back(i);
            }
            std::cout << "this is my unique column " << uniqueColumns.at(i) << " ";
        }*/

        Header newHeader = combineHeaders(uniqueColumns, inputRelation.header);
        Relation newRelation(name, newHeader);

        for (Tuple firstTuple :  rows) {
                for (Tuple secondTuple : inputRelation.rows) {
                if (IsJoinable(matchColumns, firstTuple, secondTuple)) {
                    newRelation.AddTuple(CombineTuple(uniqueColumns, firstTuple, secondTuple));
                }
            }
        }
        return newRelation;
    }

    Relation NaturalJoin1(Relation r1, Relation r2){
        Header h;
        headMap.clear();
        h = joinedHead1(r1.GetHeader(), r2.GetHeader());
        Relation r("The name of the new relation here", h);

        for(Tuple t : r1.GetTuples()){
            for(Tuple p : r2.GetTuples()){
                if(isTupleJoinable1(headMap, t, p)){
                    r.AddTuple(combineTuples1(t, p));
                }
            }
        }
        return r;
    }

    Header joinedHead1(Header one, Header two){
        std::vector<std::string> headers;
        for(int i = 0; i < two.GetHeader().size(); i++){
            for(int j = 0; j < one.GetHeader().size(); j++){
                if(one.toStringSingle(j) == two.toStringSingle(i)){
                    headMap.insert(std::pair<int, int>(i, j));
                }
            }
        }
        for(int i = 0; i < one.GetHeader().size(); i++){
            headers.push_back(one.toStringSingle(i));
        }
        for(int i = 0; i < two.GetHeader().size(); i++){
            if(headMap.find(i) == headMap.end()){
                headers.push_back(two.toStringSingle(i));
            }
        }
        Header h(headers);
        return h;
    }

    bool isTupleJoinable1(std::map<int, int> matchingCols, Tuple one, Tuple two){
        for(std::pair<int, int> match : matchingCols){
            if(one.toStringSingle(match.second) != two.toStringSingle(match.first)){
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples1(Tuple first, Tuple second){
        std::vector<std::string> vals;
        for(int i = 0; i < first.GetAttributes().size(); i++){
            vals.push_back(first.toStringSingle(i));
        }
        for(int i = 0; i < second.GetAttributes().size(); i++){
            if(headMap.find(i) == headMap.end()){
                vals.push_back(second.toStringSingle(i));
            }
        }
        Tuple t(vals);
        return t;
    }

    Relation unionize1(Relation r1, Relation r2){
        for(Tuple t : r2.GetTuples()){
            r1.AddTuple(t);
        }
        return r1;
    }

    bool myUnion(Relation inputRelation) {
        bool change = true;
        for (Tuple t: rows) {
            if (inputRelation.rows.insert(t).second) {
            }
            else {
                for (Tuple x: inputRelation.GetTuples()) {
                    rows.insert(x);
                    std::cout << x.toString() << std::endl;
                }
                change = true;
            }
        }
        /*for (Tuple t: inputRelation.rows) {
            rows.insert(t);
        }*/
        return change;
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

    std::string toStringNew(Relation oldRelation){
        std::string myNew;
        bool isNew = true;
        std::vector<Tuple> newValues;
        for(Tuple newRelation : rows){
            isNew = true;
            for(Tuple oldRela : oldRelation.GetTuples()) {
                if(oldRela.toString() == newRelation.toString()) {
                    isNew = false;
                }
            }
            if(isNew) {
                newValues.push_back(newRelation);
            }
        }

        for(unsigned int i = 0; i < newValues.size(); i++) {
            int numberAttributes = newValues.at(i).GetAttributes().size();
            for(int j = 0; j < numberAttributes; j++) {
                if (j == 0) {
                    myNew += "  " + header.toStringSingle(j) + "=";
                }
                else {
                    myNew += header.toStringSingle(j) + "=";
                }
                if (j == numberAttributes-1) {
                    myNew += newValues.at(i).toStringSingle(j);
                }
                else {
                    myNew += newValues.at(i).toStringSingle(j) + ", ";
                }
            }
            myNew += "\n";
        }
        return myNew;
    }
};


#endif //PROJECT_1_RELATION_H
