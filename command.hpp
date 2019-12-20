#pragma once

#include <memory>

#include "figure.hpp"
#include "document.hpp"

class Command {
public:
    virtual void exec() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
protected:
    std::shared_ptr<Document> document;
};

class InsertCommand : public Command {
public:
    InsertCommand(std::shared_ptr<Document> document, Figures figure, 
            Point* points) : figure(figure), points(points) {this->document = document;}; 

    void exec() override {
       document->insert(figure, points); 
    }

    void undo() override {
        document->popBack();
    }
private:
    Figures figure;
    Point* points;
};

class RemoveCommand : public Command {
public:
    RemoveCommand(std::shared_ptr<Document> document, int id) : 
        id(id), position(-1), figure(nullptr) {this->document = document;};

    void exec() override {
        try {
            figure = document->getFigure(id);
            position = document->getPosition(id);
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
            return;
        }
        document->remove(id);
    }

    void undo() override {
        document->insert(position, figure);
    }
private:
    int id;
    int position;
    std::shared_ptr<Figure> figure;
};
