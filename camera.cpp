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

// This is the actual ray casting, replace this with ray intersection algorithm:

// Function to check if a pixel is inside a polygon (simple bounding box check for now)
bool Camera::isInsidePolygon(int x, int y, const Polygon& polygon) {
    const std::vector<glm::vec3>& verts = polygon.getVertices();
    float minX = verts[0].x, maxX = verts[0].x;
    float minY = verts[0].y, maxY = verts[0].y;

    for (const auto& v : verts) {
        if (v.x < minX) minX = v.x;
        if (v.x > maxX) maxX = v.x;
        if (v.y < minY) minY = v.y;
        if (v.y > maxY) maxY = v.y;
    }

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

void Camera::render(const std::string& filename, const Scene& scene) const {
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
            glm::vec3 pixelColor(0.0f, 0.0f, 0.0f);  // Default black

            // Check if the pixel is inside any polygon
            for (const auto& polygon : scene.polygons) {
                if (isInsidePolygon(x, y, polygon)) {
                    pixelColor = polygon.getColor().toVec3();  // Use the polygon color
                    break;
                }
            }

            // Write the color to the file (convert to 0-255 range)
            outFile << static_cast<int>(pixelColor.r * 255) << " "
                    << static_cast<int>(pixelColor.g * 255) << " "
                    << static_cast<int>(pixelColor.b * 255) << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}


