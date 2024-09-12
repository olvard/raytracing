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

    scene.addRoom();
    scene.addCamera(camera);



    // Render the scene to a PPM file
    camera.render("/Users/oliverlundin/Local Documents/github/raytracer/output.ppm", colorMatrix);

    std::cout << "Rendering complete!" << std::endl;

    return 0;
}
