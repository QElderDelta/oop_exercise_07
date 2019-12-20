#pragma once

#include <memory>

#include "figure.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

class Factory {
public:
    std::shared_ptr<Figure> createFigure(Figures type, Point* p, int id) {
        if(type == Figures::Rhombus) {
            try {
                Rhombus{p, id};
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
                return nullptr;
            }
            return std::make_shared<Rhombus>(Rhombus{p, id});
        } else if(type == Figures::Pentagon) {
            return std::make_shared<Pentagon>(Pentagon{p, id});
        } else if(type == Figures::Hexagon) {
            return std::make_shared<Hexagon>(Hexagon{p, id});
        } else {
            return nullptr;
        }
    }
};
