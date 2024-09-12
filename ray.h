//
// Created by Oliver Lundin on 2024-09-12.
//

#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>


class Ray {
public:
    glm::vec3 ps; // Start point
    glm::vec3 pe; // End point

    Ray(glm::vec3 start, glm::vec3 end) : ps(start), pe(end) {} // Constructor

    glm::vec3 getDirection() const { return pe - ps; } // Get direction of ray

    glm::vec3 pointAt(float t) const { return ps + t * getDirection(); } // Get point at t

};



#endif //RAY_H
