//
// Created by Oliver Lundin on 2024-09-12.
//

#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

#include "colorDBL.h"


class Ray {
public:
    glm::vec3 ps; // Start point
    glm::vec3 pe; // End point
    colorDBL color; // Color of ray
    Ray* nextRay; // Next ray

    Ray(glm::vec3 start, glm::vec3 end, colorDBL color = colorDBL(0.0,0.0,0.0), Ray* nextRay = nullptr)
    : ps(start), pe(end), color(color), nextRay(nextRay) {} // Constructor

    glm::vec3 getDirection() const { return glm::normalize(pe - ps); } // Get direction of ray

    glm::vec3 pointAt(float t) const { return ps + t * getDirection(); } // Get point at t

};



#endif //RAY_H
