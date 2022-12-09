//
// Created by Juan on 12/6/2022.
//

#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H
#include<map>
#include<unordered_map>
#include<set>
#include<vector>
#include<algorithm>
#include <iostream>

class Graph {
private:
    std::map<int, std::set<int>> adjacencyList; //key: the rule index, object: indexes of rules I depend on
    std::map<int, std::set<int>> adjacencyListReverse;
    std::map<int, bool> myNodes;
    std::unordered_map<int, bool> myNodes2;
    std::vector<int> postOrderList;
    std::set<int> SCC;
    std::vector<std::set<int>> SCCList;

public:
    void insertRule(int from, std::set<int> to) {
        adjacencyList.insert({from, to});
    }

    void insertPostOrderList(std::vector<int> postOrderList) {
        this->postOrderList = postOrderList;
    }

    std::vector<int> dfs() {
        for (const auto &fromCopy : adjacencyList) {
            myNodes.insert({fromCopy.first, false});
        }
        for (const auto &from: myNodes) {
            if (!myNodes[from.first]) {
                dfsf(from.first);
            }
        }
        return postOrderList;
    }

    void dfsf(int from) {
        myNodes[from] = true;
        /*std::cout << "Reversed graph: " << std::endl;
        for (const auto &iterator : adjacencyList) {
            std::cout << "R" << iterator.first << ": ";
            for (const auto &iterator2: iterator.second) {
                std::cout << iterator2 << ",";
            }
            std::cout << std::endl;
        }*/
        for (const auto &to: adjacencyList[from]) {
            if (!myNodes[to]) {
                dfsf(to);
            }
        }
        /*if (postOrderList.size()==myNodes.size()) {
            return;
        }*/
        postOrderList.push_back(from);
    }

    std::vector<std::set<int>> dfsForward() {
        //std::cout << "My reversed post order List: " << std::endl;
        std::reverse(postOrderList.begin(), postOrderList.end());
       /* for (int i = 0; i < postOrderList.size(); i++) {
            std::cout << postOrderList.at(i) << std::endl;
            myNodes.insert({i, false});
        }*/

        std::cout << "Dependency Graph" << std::endl;
        std::string print;
        for (const auto &it : adjacencyList) {
            print +=  "R" + std::to_string(it.first) + ":";
            for (const auto &it2: it.second) {

                print += "R" + std::to_string(it2) + ",";
            }
            if (it.second.size() > 0) {
                print = print.substr(0, print.size() - 1);
            }
            print += "\n";
        }
        print += "\n";
        std::cout << print;

        //postOrderList.clear();

        for (unsigned int i = 0; i < postOrderList.size(); i++) {
            //std::cout << "inside of: " << postOrderList.at(i) << std::endl;
            SCC.clear();
            bool visited = false;
            if (!myNodes[postOrderList.at(i)]) {
                dfsfSCC(postOrderList.at(i));
               SCC.insert(postOrderList.at(i));
               visited = true;
            }
            if (visited) {
                SCCList.push_back(SCC);
            }
        }

        /*std::cout << "SCC List: ";
       // SCCList.push_back(SCC);
        for (int i = 0; i < SCCList.size(); i++) {
            std::cout << i << ": ";
            for (const auto &it: SCCList.at(i)) {
                std::cout << it << ", ";
            }
        }*/
        return SCCList;
    }

    void dfsfSCC(int from) {
        myNodes[from] = true;
        for (const auto &to: adjacencyList[from]) {
            //std::cout << "To the right: " << to << std::endl;
            if (!myNodes[to]) {
                dfsfSCC(to);
                SCC.insert(to);
            }
        }
    }


};


#endif //PROJECT_1_GRAPH_H
