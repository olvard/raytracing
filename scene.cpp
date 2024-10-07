//
// Created by Oliver Lundin on 2024-09-10.
//
#include "scene.h"

void Scene::addTetrahedron(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4, const colorDBL &color, float material) {
    // Define the four triangles of the tetrahedron
    std::vector<glm::vec3> face1 = {v1, v2, v3};  // CCW
    std::vector<glm::vec3> face2 = {v1, v2, v4};  // Ensure CCW
    std::vector<glm::vec3> face3 = {v2, v3, v4};  // Ensure CCW
    std::vector<glm::vec3> face4 = {v1, v4, v3};  // Ensure CCW

    // Add each triangle to the scene as a unique_ptr<Triangle>
    polygons.push_back(std::make_unique<Triangle>(face1, color, material));
    polygons.push_back(std::make_unique<Triangle>(face2, color, material));
    polygons.push_back(std::make_unique<Triangle>(face3, color, material));
    polygons.push_back(std::make_unique<Triangle>(face4, color, material));
}


void Scene::addRoom() {
    // Add a room to the scene
    // Floor
    std::vector<glm::vec3> squareVertices = {
        {0.0f, -6.0f, -5.0f},
        {10.0f, -6.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
        {0.0f, 6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices, colorDBL(0.0, 0.4, 0.0),0.0f));  // Green square

    std::vector<glm::vec3> triangleVertices_left = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, 6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_left, colorDBL(0.4, 0.0, 0.0),0.0f));  // Red triangle

    std::vector<glm::vec3> triangleVertices_right = {
        {10.0f, -6.0f, -5.0f},
        {13.0f, 0.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_right, colorDBL(0.4, 0.0, 0.0),0.0f));  // Red triangle

    // Ceiling
    std::vector<glm::vec3> squareVertices_c = {
        {0.0f, -6.0f, 5.0f},
        {0.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_c, colorDBL(0.0, 0.4, 0.0),0.0f));  // Green square

    std::vector<glm::vec3> triangleVertices_cl = {
        {0.0f, -6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {0.0f, 6.0f, 5.0f},
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_cl, colorDBL(0.4, 0.0, 0.0),0.0f));  // Red triangle

    std::vector<glm::vec3> triangleVertices_cr = {
        {10.0f, 6.0f, 5.0f},
        {13.0f, 0.0f, 5.0f},
        {10.0f, -6.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Triangle>(triangleVertices_cr, colorDBL(0.4, 0.0, 0.0),0.0f));  // Red triangle

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
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_fr, colorDBL(0.0, 0.0, 0.4),0.0f));  // front right

    std::vector<glm::vec3> squareVertices_l = {
        {0.0f, 6.0f, 5.0f},
        {0.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, 5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_l, colorDBL(0.0, 0.0, 0.4),0.0f));  // Blue square

    std::vector<glm::vec3> squareVertices_r = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_r, colorDBL(0.4, 0.0, 0.0),0.0f));  // Blue square

    std::vector<glm::vec3> squareVertices_bl = {
        {0.0f, 6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {-3.0f, 0.0f, -5.0f},
        {0.0f, 6.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_bl, colorDBL(0.0, 0.4, 0.4),0.0f));  //back left wall

    std::vector<glm::vec3> squareVertices_br = {
        {-3.0f, 0.0f, 5.0f},
        {0.0f, -6.0f, 5.0f},
        {0.0f, -6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    polygons.push_back(std::make_unique<Rectangle>(squareVertices_br, colorDBL(0.0, 0.4, 0.4),0.0f));  // back right wall

    // Add objects

    glm::vec3 v1(6.0f, 0.0f, -4.0f);
    glm::vec3 v2(8.0f, -2.0f, -4.0f);
    glm::vec3 v3(8.0f, 2.0f, -4.0f);
    glm::vec3 v4(7.0f, 0.0f, -2.0f);
    addTetrahedron(v1, v2, v3, v4, colorDBL(0.7, 0.2, 0.5), 0.0f);

    //Lights
    lights.emplace_back(
    glm::vec3(2, -2, 4), glm::vec3(2, 2, 4), glm::vec3(6, 2, 4), glm::vec3(6, -2, 4),colorDBL(1.0, 1.0, 1.0)
    );

    lights.back().debugPrint();
}