//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef COLORDBL_H
#define COLORDBL_H

#include <glm/glm.hpp>

class colorDBL {
public:
    // Constructor
    double r, g, b;
    colorDBL(double r, double g, double b) : color(r, g, b) {}

    //default constructor initializes to black
    colorDBL(): color(0.0, 0.0, 0.0), r(0.0), g(0.0), b(0.0) {}

    // Convert color to glm::vec3
    glm::vec3 toVec3() const { return color; }

protected:
    glm::vec3 color;


};
#endif //COLORDBL_H
