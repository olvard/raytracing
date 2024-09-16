//
// Created by Oliver Lundin on 2024-09-10.
//

#include "camera.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>

Camera::Camera(const glm::vec3& eye, const glm::vec3& c1, const glm::vec3& c2,
         const glm::vec3& c3, const glm::vec3& c4, int width, int height)
          : eye(eye), c1(c1), c2(c2), c3(c3), c4(c4), width(width), height(height) {
    pixels.resize(height, std::vector<colorDBL>(width)); //Create a 2D array of pixels for the camera
}

Ray Camera::createRay(int x, int y) const {
    float u = static_cast<float>(x) / width;
    float v = static_cast<float>(y) / height;
    // Calculate point on the image plane with bilinear interpolation
    glm::vec3 point = (1-u)*(1-v)*c1 + u*(1-v)*c2 + u*v*c3 + (1-u)*v*c4;
    return Ray(eye, point);
}

colorDBL Camera::traceRay(const Ray &ray, const Scene &scene) const {
    float closest_t = std::numeric_limits<float>::max();
    const Polygon* hit_polygon = nullptr;
    glm::vec3 hit_point;

    //Loop through the polygons in the scene
    for (const auto& polygon : scene.polygons) {
        float t;
        glm::vec3 intersectionPoint;
        if (polygon->intersect(ray, t, intersectionPoint)) {
            if(t < closest_t) {
                closest_t = t;
                hit_polygon = polygon.get();
                hit_point = intersectionPoint;
            }
        }
    }

    //return the color of the hit polygon
    if(hit_polygon) {
        return hit_polygon->getColor();
    }

    //else return black
    return colorDBL(0,0,0);
}



void Camera::render(const std::string& filename, const Scene& scene)  {
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Ray ray = createRay(i, j);
            pixels[j][i] = traceRay(ray,scene);
        }
    }

    // Find the maximum color value
    double max_value = 0;
    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            max_value = std::max({max_value, pixel.r, pixel.g, pixel.b});
        }
    }

    // Normalize and write to file
    std::ofstream out(filename, std::ios::binary);
    out << "P6\n" << width << " " << height << "\n255\n";

    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            char r = static_cast<char>(std::min(255.0, pixel.r / max_value * 255));
            char g = static_cast<char>(std::min(255.0, pixel.g / max_value * 255));
            char b = static_cast<char>(std::min(255.0, pixel.b / max_value * 255));
            out.write(&r, 1);
            out.write(&g, 1);
            out.write(&b, 1);
        }
    }
}


