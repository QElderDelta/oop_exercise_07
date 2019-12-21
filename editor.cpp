#include "editor.hpp"

void Editor::createDocument() {
    document = std::make_shared<Document>();
    while(!commandStack.empty()) {
        commandStack.pop();
    }
}

void Editor::insert() {
    std::shared_ptr<Command> command = std::shared_ptr<Command>(new InsertCommand(document));
    command->exec();
    commandStack.push(command);
}

void Editor::remove(int id) {
    try {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new RemoveCommand(document, id));
        command->exec();
        commandStack.push(command);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Editor::saveDocument(const std::string& filename) {
    document->save(filename);
}

void Editor::loadDocument(const std::string& filename) {
    createDocument();
    document->load(filename);
}

void Editor::undo() {
    if(commandStack.empty()) {
        throw std::logic_error("Nothing to undo");
    }
    std::shared_ptr<Command> command = commandStack.top();
    command->undo();
    commandStack.pop();
}

void Editor::print() {
    document->print();
}
