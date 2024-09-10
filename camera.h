//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "polygon.h"
#include <glm/glm.hpp>
#include "scene.h"


class Camera {
private:
    int width;
    int height;
    glm::vec3 eye;
    glm::vec3 c1,c2,c3,c4;


public:
    Camera(const glm::vec3& eye, const glm::vec3& c1, const glm::vec3& c2,
           const glm::vec3& c3, const glm::vec3& c4, int width, int height) : eye(eye), c1(c1), c2(c2), c3(c3), c4(c4), width(width), height(height) {}

    void render(const std::string& filename, const Scene& scene) const;

    static bool isInsidePolygon(int x, int y, const Polygon& polygon);

};

#endif //CAMERA_H
