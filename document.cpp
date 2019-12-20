#include "document.hpp"


void Document::newDocument() {
    content.clear();
    currentFigureID = 0;
}

void Document::save(const std::string& fileName) {
    serialize(fileName);
}

void Document::load(const std::string& fileName) {
    deserialize(fileName);
}

void Document::print() {
    for(const auto& figure : content) {
        figure->Print(std::cout);
    }
}

void Document::insert() {
    std::shared_ptr<Figure> figure = this->factory.createFigure(currentFigureID);
    if(figure) {
        content.push_back(figure);
        currentFigureID++;
    }
}

void Document::insert(unsigned position, std::shared_ptr<Figure> figure) {
    auto it = content.begin();
    std::advance(it, position);
    content.insert(it, figure);
}

void Document::remove(int id) {
    unsigned temp = content.size();
    auto it = std::remove_if(content.begin(), content.end(), [id](std::shared_ptr<Figure> f)
            {return id == f->getID();});
    content.erase(it, content.end());
    if(temp == content.size()) {
        throw std::invalid_argument("Figure this such ID doesn't exist");
    }
}

void Document::popBack() {
    if(!content.size()) {
        throw std::logic_error("Document is empty");
    }
    content.pop_back();
}

std::shared_ptr<Figure> Document::getFigure(int id) {
    for(const auto& figure : content) {
        if(id == figure->getID()) {
            return figure;
        }
    }
    throw std::invalid_argument("1:No figure this such ID");
}

int Document::getPosition(int id) {
    int n = content.size();
    for(int i = 0; i < n; ++i) {
        if(id == content[i]->getID()) {
            return i;
        }
    }
    throw std::invalid_argument("2:No figure with such ID");
}

void Document::serialize(const std::string& fileName) {
    std::ofstream os(fileName, std::ios::trunc);
    if(!os) {
        throw std::runtime_error("Couldn't open file");
    }
    os << content.size() << std::endl;
    for(const auto& figure : content) {
        figure->serialize(os);
    }
}

void Document::deserialize(const std::string& fileName) {
    std::ifstream is(fileName);
    if(!is) {
        throw std::runtime_error("Couldn't open file");
    }
    this->newDocument();
    int numberOfFigures;
    is >> numberOfFigures;
    while(numberOfFigures--) {
        this->insert();
    }
}
