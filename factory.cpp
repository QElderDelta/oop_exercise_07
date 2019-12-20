#include "factory.hpp"

std::shared_ptr<Figure> Factory::createFigure(int id) {
    std::string figureType;
    std::cin >> figureType;
    std::shared_ptr<Figure> figure;
    if(figureType == "R") {
        try {
            figure = std::make_shared<Rhombus>(Rhombus{std::cin, id});
        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    } else if(figureType == "P") {
        figure = std::make_shared<Pentagon>(Pentagon{std::cin, id});
    } else if(figureType == "H") {
        figure = std::make_shared<Hexagon>(Hexagon{std::cin, id});
    } else {
        std::cout << "Unknown figure" << std::endl;
    }
    return figure;
}
