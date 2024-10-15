#include <iostream>
#include <glm/glm.hpp>
#include "scene.h"
#include "camera.h"

int main() {
    // Create a scene
    Scene scene;
    scene.addRoom();

    // create a camera
    glm::vec3 eye = glm::vec3(-1.0f, 0.0f, 0.0f);  // Camera at (-1, 0, 0)
    glm::vec3 c1 = glm::vec3(0.0f, -1.0f, -1.0f);
    glm::vec3 c2 = glm::vec3(0.0f, 1.0f, -1.0f);
    glm::vec3 c3 = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 c4 = glm::vec3(0.0f, -1.0f, 1.0f);
    Camera camera(eye, c1, c2, c3, c4, 800, 600);  // Initialize the camera

    // Render the scene to a PPM file
    camera.render("/Users/oliverlundin/Local Documents/github/raytracer/output.ppm", scene, 0);

    std::cout << "Rendering complete!" << std::endl;

    return 0;
}
