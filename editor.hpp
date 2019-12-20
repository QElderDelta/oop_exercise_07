#pragma once

#include <stack>

#include "command.hpp"
#include "document.hpp"
#include "figure.hpp"

class Editor {
public:    
    Editor() : document(nullptr) {};

    void createDocument() {
        document = std::make_shared<Document>();
    }

    void insert(Figures figure, Point* points) {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new InsertCommand(document, figure, points));
        command->exec();
        commandStack.push(command);
    }

    void remove(int id) {
        try {
            std::shared_ptr<Command> command = std::shared_ptr<Command>(new RemoveCommand(document, id));
            command->exec();
            commandStack.push(command);
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void saveDocument(const std::string& filename) {
        document->save(filename);
    }

    void loadDocument(const std::string& filename) {
        createDocument();
        document->load(filename);
    }

    void undo() {
        if(commandStack.empty()) {
            throw std::logic_error("Nothing to undo");
        }
        std::shared_ptr<Command> command = commandStack.top();
        command->undo();
        commandStack.pop();
    }

    void print() {
        document->print();
    }
private:
    std::shared_ptr<Document> document;
    std::stack<std::shared_ptr<Command>> commandStack;
};
