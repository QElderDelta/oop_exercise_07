#pragma once

#include <memory>
#include <string>

#include "figure.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

class Factory {
public:
    std::shared_ptr<Figure> createFigure(int id);
};
