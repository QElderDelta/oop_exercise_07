#include <iostream>
#include <string>

#include "editor.hpp"

void help() {
    std::cout << "new - Creates new document" << std::endl;
    std::cout << "save <path to file> - saves document to file" << std::endl;
    std::cout << "load <path to file> - loads document from file" << std::endl;
    std::cout << "add R/P/H <coordinates> - adds Rhombus/Pentagon/Hexagon to the document" << std::endl;
    std::cout << "remove <Figure ID> - removes figure with given ID if it is present" << std::endl;
    std::cout << "undo - undo last action" << std::endl;
    std::cout << "print - prints information about all figures from document" << std::endl;
    std::cout << "help - do I really need to explain what help does?" << std::endl;
    std::cout << "exit - exit editor" << std::endl;
}

int main() {
    int id;
    std::string command;
    std::string filepath;
    std::string figureType;
    Editor e;
    help();
    while(std::cin >> command) {
        if(command == "new") {
            e.createDocument();
        } else if(command == "save") {
            std::cin >> filepath;
            try {
                e.saveDocument(filepath);
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else if(command == "load") {
            std::cin >> filepath;
            try {
                e.loadDocument(filepath);
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }    
        } else if(command == "add") {
            e.insert();
        } else if(command == "remove") {
            std::cin >> id;
            try {
                e.remove(id);
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }    
        } else if(command == "undo") {
            try {
                e.undo();
            } catch(std::exception& e) { 
                std::cout << e.what() << std::endl;
            }   
        } else if(command == "print") {
            e.print();
        } else if(command == "help") {
            help();
        } else if(command == "exit") {
            break;
        } else {
            std::cout << "Unknown figure" << std::endl;
        }
    }
    return 0;
}
