#include "command.hpp"


void InsertCommand::exec() {
   document->insert(); 
}

void InsertCommand::undo() {
    document->popBack();
}


void RemoveCommand::exec() {
    try {
        figure = document->getFigure(id);
        position = document->getPosition(id);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    document->remove(id);
}

void RemoveCommand::undo() {
    document->insert(position, figure);
}
