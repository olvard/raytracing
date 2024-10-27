//
// Created by Oliver Lundin on 2024-09-10.
//
#include "scene.h"


void Scene::addTetrahedron(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4, const colorDBL &color, Material material) {
    // Define the four triangles of the tetrahedron
    std::vector<glm::vec3> face1 = {v1, v2, v3};  // CCW
    std::vector<glm::vec3> face2 = {v1, v2, v4};  // Ensure CCW
    std::vector<glm::vec3> face3 = {v2, v3, v4};  // Ensure CCW
    std::vector<glm::vec3> face4 = {v1, v4, v3};  // Ensure CCW

    // Add each triangle to the scene as a unique_ptr<Triangle>
    shapes.push_back(std::make_unique<Triangle>(face1, color, material));
    shapes.push_back(std::make_unique<Triangle>(face2, color, material));
    shapes.push_back(std::make_unique<Triangle>(face3, color, material));
    shapes.push_back(std::make_unique<Triangle>(face4, color, material));
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
    shapes.push_back(std::make_unique<Rectangle>(squareVertices, colorDBL(0.7, 0.7, 0.7), Material(Material::DIFFUSE)));  // Green square

    std::vector<glm::vec3> triangleVertices_left = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, 6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    shapes.push_back(std::make_unique<Triangle>(triangleVertices_left, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Red triangle

    std::vector<glm::vec3> triangleVertices_right = {
        {10.0f, -6.0f, -5.0f},
        {13.0f, 0.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
    };
    shapes.push_back(std::make_unique<Triangle>(triangleVertices_right, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Red triangle

    // Ceiling
    std::vector<glm::vec3> squareVertices_c = {
        {0.0f, -6.0f, 5.0f},
        {0.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_c, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Green square

    std::vector<glm::vec3> triangleVertices_cl = {
        {0.0f, -6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {0.0f, 6.0f, 5.0f},
    };
    shapes.push_back(std::make_unique<Triangle>(triangleVertices_cl, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Red triangle

    std::vector<glm::vec3> triangleVertices_cr = {
        {10.0f, 6.0f, 5.0f},
        {13.0f, 0.0f, 5.0f},
        {10.0f, -6.0f, 5.0f}
    };
    shapes.push_back(std::make_unique<Triangle>(triangleVertices_cr, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Red triangle

    // Walls
    std::vector<glm::vec3> squareVertices_fl = {
        {10.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, -5.0f},
        {13.0f, 0.0f, -5.0f},
        {13.0f, 0.0f, 5.0f}

    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_fl, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // Mirror

    std::vector<glm::vec3> squareVertices_fr = {
        {13.0f, 0.0f, 5.0f},
        {13.0f, 0.0f, -5.0f},
        {10.0f, -6.0f, -5.0f},
        {10.0f, -6.0f, 5.0f}
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_fr, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // front right

    std::vector<glm::vec3> squareVertices_l = {
        {0.0f, 6.0f, 5.0f},
        {0.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, 5.0f}
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_l, colorDBL(0.0, 0.0, 0.6),Material(Material::DIFFUSE)));  // Blue square

    std::vector<glm::vec3> squareVertices_r = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, -5.0f}
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_r, colorDBL(0.6, 0.0, 0.0),Material(Material::DIFFUSE)));  // Blue square

    std::vector<glm::vec3> squareVertices_bl = {
        {0.0f, 6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {-3.0f, 0.0f, -5.0f},
        {0.0f, 6.0f, -5.0f}
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_bl, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  //back left wall

    std::vector<glm::vec3> squareVertices_br = {
        {-3.0f, 0.0f, 5.0f},
        {0.0f, -6.0f, 5.0f},
        {0.0f, -6.0f, -5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    shapes.push_back(std::make_unique<Rectangle>(squareVertices_br, colorDBL(0.7, 0.7, 0.7),Material(Material::DIFFUSE)));  // back right wall

    // Add objects

    glm::vec3 v1(4.0f, 2.0f, -5.0f); // front
    glm::vec3 v2(6.0f, 0.0f, -5.0f); // right
    glm::vec3 v3(6.0f, 4.0f, -5.0f); // left
    glm::vec3 v4(5.0f, 2.0f, -2.0f); // top
    addTetrahedron(v1, v2, v3, v4, colorDBL(0.7, 0.2, 0.5), Material(Material::DIFFUSE));

    // add sphere
    addSphere(glm::vec3(6.0f, -2.0f, -1.0f), 2.0f, colorDBL(0.7, 0.2, 0.3), Material(Material::MIRROR));

    // Light
    std::vector<glm::vec3> lightVertices = {
        {2.0f, -1.0f, 4.9f},
        {2.0f, 1.0f, 4.9f},
        {6.0f, -1.0f, 4.9f},
        {6.0f, 1.0f, 4.9f},

    };
    shapes.push_back(std::make_unique<Rectangle>(lightVertices, colorDBL(1.0, 1.0, 1.0), Material(Material::LIGHT)));

    // Lights array
    lights.emplace_back(
        glm::vec3(0.0f, 1.0f, 4.8f), glm::vec3(6.0f, 1.0f, 4.8f), glm::vec3(6.0f, -1.0f, 4.8f), glm::vec3(0.0f, -1.0f, 4.8f), colorDBL(1.0, 1.0, 1.0)
    );


    lights.back().debugPrint();
}