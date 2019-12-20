#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>

#include "figure.hpp"
#include "factory.hpp"
#include "command.hpp"

class Document {
friend class Command;    
public:
    Document() : currentFigureID(0) {};
    
    void newDocument() {
        content.clear();
        currentFigureID = 0;
    }

    void save(const std::string& fileName) {
        serialize(fileName);
    }

    void load(const std::string& fileName) {
        deserialize(fileName);
    }

    void print() {
        for(const auto& figure : content) {
            figure->Print(std::cout);
        }
    }

    void insert(Figures type, Point* points) {
        if(type == Figures::Rhombus) {
            try {
                Rhombus{points, currentFigureID};
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return;
            }
            content.push_back(factory.createFigure(Figures::Rhombus, points, currentFigureID));
        } else if(type == Figures::Pentagon) {
            content.push_back(factory.createFigure(Figures::Pentagon, points, currentFigureID));
        } else if(type == Figures::Hexagon) {
            content.push_back(factory.createFigure(Figures::Hexagon, points, currentFigureID));
        }
        currentFigureID++;
    }

    void insert(unsigned position, std::shared_ptr<Figure> figure) {
        auto it = content.begin();
        std::advance(it, position);
        content.insert(it, figure);
    }

    void remove(int id) {
        unsigned temp = content.size();
        auto it = std::remove_if(content.begin(), content.end(), [id](std::shared_ptr<Figure> f)
                {return id == f->getID();});
        content.erase(it, content.end());
        if(temp == content.size()) {
            throw std::invalid_argument("Figure this such ID doesn't exist");
        }
    }

    void popBack() {
        if(!content.size()) {
            throw std::logic_error("Document is empty");
        }
        content.pop_back();
    }

    std::shared_ptr<Figure> getFigure(int id) {
        for(const auto& figure : content) {
            if(id == figure->getID()) {
                return figure;
            }
        }
        throw std::invalid_argument("1:No figure this such ID");
    }

    int getPosition(int id) {
        int n = content.size();
        for(int i = 0; i < n; ++i) {
            if(id == content[i]->getID()) {
                return i;
            }
        }
        throw std::invalid_argument("2:No figure with such ID");
    }
private:
    int currentFigureID;
    std::vector<std::shared_ptr<Figure>> content;
    Factory factory;
    void serialize(const std::string& fileName) {
        std::ofstream os(fileName, std::ios::trunc);
        if(!os) {
            throw std::runtime_error("Couldn't open file");
        }
        os << content.size() << std::endl;
        for(const auto& figure : content) {
            figure->serialize(os);
        }
    }

    void deserialize(const std::string& fileName) {
        std::ifstream is(fileName);
        if(!is) {
            throw std::runtime_error("Couldn't open file");
        }
        this->newDocument();
        int numberOfFigures;
        is >> numberOfFigures;
        int numberOfPoints;
        Point p;
        while(numberOfFigures--) {
            is >> numberOfPoints;
            Point* points = new Point[numberOfPoints]; 
            for(int i = 0; i < numberOfPoints; ++i) {
                is >> p;
                points[i] = p;
            }
            if(numberOfPoints == 4) {
                content.push_back(factory.createFigure(Figures::Rhombus, points, currentFigureID));
            } else if(numberOfPoints == 5) {
                content.push_back(factory.createFigure(Figures::Pentagon, points, currentFigureID));
            } else if(numberOfPoints == 6) {
                content.push_back(factory.createFigure(Figures::Hexagon, points, currentFigureID));
            }
            this->currentFigureID++;
            delete[] points;
        }
    }
};
