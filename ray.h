//
// Created by Oliver Lundin on 2024-09-12.
//

#ifndef RAY_H
#define RAY_H

#include <memory>
#include <glm/glm.hpp>

#include "colorDBL.h"


class Ray {
public:
    glm::vec3 ps; // Start point
    glm::vec3 pe; // End point
    colorDBL color; // Color of ray
    std::shared_ptr<Ray> nextRay;

    Ray(glm::vec3 start, glm::vec3 end, colorDBL color = colorDBL(0.0,0.0,0.0))
    : ps(start), pe(end), color(color), nextRay(nullptr) {} // Constructor

    glm::vec3 getDirection() const { return glm::normalize(pe - ps); } // Get direction of ray

    glm::vec3 pointAt(float t) const { return ps + t * getDirection(); } // Get point at t

    void setNextRay(std::shared_ptr<Ray> next) { nextRay = next; }
    std::shared_ptr<Ray> getNextRay() const { return nextRay; }

};



#endif //RAY_H
