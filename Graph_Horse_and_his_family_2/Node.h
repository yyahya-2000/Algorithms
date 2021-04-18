//
// Created by Yanal on 4/18/2021.
//
#include <string>
#include <vector>

class Node {
public:
    std::string name;
    std::vector<Node*> neighbours;
    bool visited = false;
    Node(std::string& name) : name(name){};
};