#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>

#include "figure.hpp"
#include "factory.hpp"

class Document {
friend class Command;    
public:
    Document() : currentFigureID(0) {};
    void newDocument();
    void save(const std::string& fileName);
    void load(const std::string& fileName);
    void print();
    void insert();
    void insert(unsigned position, std::shared_ptr<Figure> figure);
    void remove(int id);
    void popBack();
    std::shared_ptr<Figure> getFigure(int id);
    int getPosition(int id);
private:
    int currentFigureID;
    std::vector<std::shared_ptr<Figure>> content;
    Factory factory;
    void serialize(const std::string& fileName);
    void deserialize(const std::string& fileName);
};
