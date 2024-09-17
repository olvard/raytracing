//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef COLORDBL_H
#define COLORDBL_H

#include <glm/glm.hpp>

class colorDBL {
public:
    // Constructor
    explicit colorDBL(double r = 0.0, double g = 0.0, double b = 0.0) : color(r, g, b) {}

    // Getters
    double r() const { return color.r; }
    double g() const { return color.g; }
    double b() const { return color.b; }

    // Convert color to glm::vec3
    glm::vec3 toVec3() const { return color; }

protected:
    glm::vec3 color;


};
#endif //COLORDBL_H
