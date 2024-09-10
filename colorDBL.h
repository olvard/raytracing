//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef COLORDBL_H
#define COLORDBL_H

#include <glm/glm.hpp>

class colorDBL {
private:
    glm::vec3 color;

public:
    // Constructor
    colorDBL(float r, float g, float b) : color(r, g, b) {}

    // Convert color to glm::vec3
    glm::vec3 toVec3() const { return color; }
};
#endif //COLORDBL_H
