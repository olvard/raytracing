#include <iostream>
#include <glm/glm.hpp>
#include "polygon.h"
#include "colorDBL.h"
#include "scene.h"
#include "camera.h"

int main() {
    // Create a scene
    glm::vec3 eye = glm::vec3(-1, 0, 0);  // Camera at (-1, 0, 0)
    glm::vec3 c1 = glm::vec3(0, -1, -1);
    glm::vec3 c2 = glm::vec3(0, 1, -1);
    glm::vec3 c3 = glm::vec3(0, 1, 1);
    glm::vec3 c4 = glm::vec3(0, -1, 1);

    Camera camera(eye, c1, c2, c3, c4, 800, 600);  // Initialize the camera
    Scene scene;

    // Create some polygons
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

    // Add polygons to the scene
    scene.addPolygon(triangle_l);
    scene.addPolygon(triangle_r);
    scene.addPolygon(square);

    // Render the scene to a PPM file
    camera.render("/Users/oliverlundin/Local Documents/github/raytracer/output.ppm", scene);

    std::cout << "Rendering complete!" << std::endl;

    return 0;
}
