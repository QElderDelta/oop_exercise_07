#pragma once

#include <memory>

#include "document.hpp"
#include "figure.hpp"

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
    InsertCommand(std::shared_ptr<Document> document) {this->document = document;};
    void exec() override;
    void undo() override;
};

class RemoveCommand : public Command {
public:
    RemoveCommand(std::shared_ptr<Document> document, int id) : 
        id(id), position(-1), figure(nullptr) {this->document = document;};
    void exec() override;
    void undo() override;
private:
    int id;
    int position;
    std::shared_ptr<Figure> figure;
};
