#pragma once

#include <stack>

#include "command.hpp"
#include "document.hpp"
#include "figure.hpp"

class Editor {
public:    
    Editor() : document(nullptr) {};
    void createDocument();
    void insert();
    void remove(int id);
    void saveDocument(const std::string& filename);
    void loadDocument(const std::string& filename);
    void undo();
    void print();
private:
    std::shared_ptr<Document> document;
    std::stack<std::shared_ptr<Command>> commandStack;
};
