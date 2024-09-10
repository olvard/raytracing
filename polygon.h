//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef POLYGON_H
#define POLYGON_H


#include <glm/glm.hpp>
#include <vector>
#include "colorDBL.h"

class Polygon {
protected:

    std::vector<glm::vec3> vertices;
    colorDBL color;

public:
    int numSides;
    Polygon(int sides, const std::vector<glm::vec3>& verts, const colorDBL& col) : numSides(sides), vertices(verts), color(col)
    {}

    const std::vector<glm::vec3>& getVertices() const { return vertices; }

    const colorDBL& getColor() const { return color; }


};
#endif //POLYGON_H
