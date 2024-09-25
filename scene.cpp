//
// Created by Oliver Lundin on 2024-09-10.
//
#include "scene.h"

void Scene::addRoom() {
    // Add a room to the scene
    // Floor
    std::vector<glm::vec3> squareVertices = {
        {0.0f, -6.0f, -5.0f},
        {10.0f, -6.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
        {0.0f, 6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices, colorDBL(0.0, 1.0, 0.0),0.0f));  // Green square

    std::vector<glm::vec3> triangleVertices_left = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, 6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_left, colorDBL(1.0, 0.0, 0.0),0.0f));  // Red triangle

    std::vector<glm::vec3> triangleVertices_right = {
        {10.0f, -6.0f, -5.0f},
        {13.0f, 0.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_right, colorDBL(1.0, 0.0, 0.0),0.0f));  // Red triangle

    // Ceiling
    std::vector<glm::vec3> squareVertices_c = {
        {0.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, 6.0f, 5.0f},
        {0.0f, 6.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_c, colorDBL(0.0, 1.0, 0.0),0.0f));  // Green square

    std::vector<glm::vec3> triangleVertices_cl = {
        {0.0f, -6.0f, 5.0f},
        {0.0f, 6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_cl, colorDBL(1.0, 0.0, 0.0),0.0f));  // Red triangle

    std::vector<glm::vec3> triangleVertices_cr = {
        {10.0f, -6.0f, 5.0f},
        {13.0f, 0.0f, 5.0f},
        {10.0f, 6.0f, 5.0f},
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_cr, colorDBL(1.0, 0.0, 0.0),0.0f));  // Red triangle

    // Walls
    std::vector<glm::vec3> squareVertices_fl = {
        {10.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, -5.0f},
        {13.0f, 0.0f, -5.0f},
        {13.0f, 0.0f, 5.0f}

    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_fl, colorDBL(1.0, 1.0, 1.0),1.0f));  // Mirror

    std::vector<glm::vec3> squareVertices_fr = {
        {13.0f, 0.0f, 5.0f},
        {13.0f, 0.0f, -5.0f},
        {10.0f, -6.0f, -5.0f},
        {10.0f, -6.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_fr, colorDBL(0.0, 0.0, 1.0),0.0f));  // front right

    std::vector<glm::vec3> squareVertices_l = {
        {0.0f, 6.0f, 5.0f},
        {0.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_l, colorDBL(0.0, 0.0, 1.0),0.0f));  // Blue square

    std::vector<glm::vec3> squareVertices_r = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_r, colorDBL(1.0, 0.0, 0.0),0.0f));  // Blue square

    std::vector<glm::vec3> squareVertices_bl = {
        {0.0f, 6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {-3.0f, 0.0f, -5.0f},
        {0.0f, 6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_bl, colorDBL(0.0, 1.0, 1.0),0.0f));  //back left wall

    std::vector<glm::vec3> squareVertices_br = {
        {-3.0f, 0.0f, 5.0f},
        {0.0f, -6.0f, 5.0f},
        {0.0f, -6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_br, colorDBL(0.0, 1.0, 1.0),0.0f));  // back right wall
}