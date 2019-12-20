#pragma once

#include <iostream>
#include <array>

#include "figure.hpp"
#include "point.hpp"

class Hexagon : public Figure {
public:
    Hexagon(Point* p, int id);
    Hexagon(std::istream& is, int id);
    Point Center() const override;
    double Square() const override;
    void Print(std::ostream& os) const override;
    int getID() const override;
    void serialize(std::ostream& os) const override;
private:
    std::array<Point, 6> points;
    int id;
};

