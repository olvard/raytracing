//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "colorDBL.h"
#include "scene.h"


class Camera {
public:

    Camera(const glm::vec3& eye, const glm::vec3& c1, const glm::vec3& c2,
           const glm::vec3& c3, const glm::vec3& c4, int width, int height);

    void render(const std::string& filename, const Scene& scene, int depth);

private:
    int width, height;
    glm::vec3 eye;
    glm::vec3 c1,c2,c3,c4;
    std::vector<std::vector<colorDBL>> pixels;

    Ray createRay(int x, int y) const;
    float calculateDirectLight(const glm::vec3& hitPoint, const glm::vec3& hitPointNormal, const Scene& scene) const;
    colorDBL traceRay(Ray& ray, const Scene& scene, int depth) const;

    void renderSegment(int startRow, int endRow, const Scene &scene, int depth);
};

#endif //CAMERA_H
