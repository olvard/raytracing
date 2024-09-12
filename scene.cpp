//
// Created by Oliver Lundin on 2024-09-10.
//
#include "scene.h"

void Scene::addRoom() {
    // Add a room to the scene
    // Floor
    std::vector<glm::vec3> triangleVertices_left = {
        {0.0f, 6.0f, 0.0f},
        {0.0f, -6.0f, 0.0f},
        {-3.0f, 0.0f, 0.0f}
    };
    Polygon triangle_l(3, triangleVertices_left, colorDBL(1.0f, 0.0f, 0.0f));  // Red triangle


    std::vector<glm::vec3> triangleVertices_right= {
        {10.0f, 6.0f, 0.0f},
        {13.0f, 0.0f, 0.0f},
        {10.0f, -6.0f, 0.0f}
    };
    Polygon triangle_r(3, triangleVertices_right, colorDBL(1.0f, 0.0f, 0.0f));  // Red triangle

    std::vector<glm::vec3> squareVertices = {
        {0.0f, 6.0f, 0.0f},
        {10.0f, 6.0f, 0.0f},
        {0.0f, -6.0f, 0.0f},
        {10.0f, -6.0f, 0.0f}
    };
    Polygon square(4, squareVertices, colorDBL(0.0f, 1.0f, 0.0f));  // Green square

    //Walls

    //front left wall
    std::vector<glm::vec3> squareVertices_fl = {
        {10.0f, 6.0f, -5.0f},
        {10.0f, 6.0f, 5.0f},
        {13.0f, 0.0f, 5.0f},
        {13.0f, 0.0f, -5.0f}
    };
    Polygon square_fl(4, squareVertices_fl, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //front right wall
    std::vector<glm::vec3> squareVertices_fr = {
        {13.0f, 0.0f, -5.0f},
        {13.0f, 0.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, -5.0f}
    };
    Polygon square_fr(4, squareVertices_fr, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //left wall
    std::vector<glm::vec3> squareVertices_l = {
        {0.0f, 6.0f, -5.0f},
        {0.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, 5.0f},
        {10.0f, 6.0f, -5.0f}
    };
    Polygon square_l(4, squareVertices_l, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //right wall
    std::vector<glm::vec3> squareVertices_r = {
        {0.0f, -6.0f, -5.0f},
        {0.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, 5.0f},
        {10.0f, -6.0f, -5.0f}
    };
    Polygon square_r(4, squareVertices_r, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //back left wall
    std::vector<glm::vec3> squareVertices_bl = {
        {0.0f, 6.0f, -5.0f},
        {0.0f, 6.0f, 5.0f},
        {-3.0f, 0.0f, 5.0f},
        {-3.0f, 0.0f, -5.0f}
    };
    Polygon square_bl(4, squareVertices_bl, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //back right wall
    std::vector<glm::vec3> squareVertices_br = {
        {-3.0f, 0.0f, -5.0f},
        {-3.0f, 0.0f, 5.0f},
        {0.0f, -6.0f, 5.0f},
        {0.0f, -6.0f, -5.0f}
    };
    Polygon square_br(4, squareVertices_br, colorDBL(0.0f, 0.0f, 1.0f));  // Blue square

    //add floor
    this->addPolygon(triangle_l);
    this->addPolygon(triangle_r);
    this->addPolygon(square);

    //add walls
    this->addPolygon(square_fl);
    this->addPolygon(square_fr);
    this->addPolygon(square_l);
    this->addPolygon(square_r);
    this->addPolygon(square_bl);
    this->addPolygon(square_br);

}