//
// Created by Oliver Lundin on 2024-09-10.
//

#include "camera.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include "polygon.h"
#include "scene.h"



void Camera::render(const std::string& filename, const std::vector<std::vector<colorDBL>>& colorMatrix) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Write the PPM header
    outFile << "P3\n" << width << " " << height << "\n255\n";

    // Loop through each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            const glm::vec3 pixelColor = colorMatrix[x][y].toVec3();

            // Write the color to the file (convert to 0-255 range)
            outFile << static_cast<int>(pixelColor.r * 255) << " "
                    << static_cast<int>(pixelColor.g * 255) << " "
                    << static_cast<int>(pixelColor.b * 255) << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}


