//
// Created by Oliver Lundin on 2024-09-10.
//
#include "polygon.h"

 glm::vec3 Polygon::getNormal() const {
     //calculate normal for triangle
     glm::vec3 v1 = vertices[1] - vertices[0];
     glm::vec3 v2 = vertices[2] - vertices[0];
     glm::vec3 normal = glm::cross(v1, v2);
     return glm::normalize(normal);
 }
