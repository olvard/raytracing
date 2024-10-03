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
    float u = 1.0f - static_cast<float>(x) / width;
    float v = 1.0f - static_cast<float>(y) / height;
    // Calculate point on the image plane with bilinear interpolation
    glm::vec3 point = (1-u)*(1-v)*c1 + u*(1-v)*c2 + u*v*c3 + (1-u)*v*c4;
    return Ray(eye, point);
}

float Camera::calculateDirectLight(const glm::vec3 &hitPoint, const glm::vec3 &hitPointNormal, const Scene &scene) const {
    float irradiance = 0.0f; //Initialize the direct light to black
    const int samples = 100;

    for(const auto& light : scene.lights) {
        for(int i = 0; i < samples; i++) {
            glm::vec3 pointOnLight = light.getRandomPoint();
            glm::vec3 direction = glm::normalize(pointOnLight - hitPoint);
            float distanceToLight = glm::distance(pointOnLight, hitPoint);

            float cosTheta = glm::dot(hitPointNormal,direction);
            float cosThetaLight = glm::dot(-light.normal,direction);

            Ray shadowRay(hitPoint + hitPointNormal * 0.001f, pointOnLight);
            bool inShadow = false;
            for(const auto& polygon : scene.polygons) {
                float t;
                glm::vec3 intersectionPoint;
                if(polygon->intersect(shadowRay, t, intersectionPoint) && t < distanceToLight) {
                    inShadow = false;
                    break;
                }
            }

            if (!inShadow) {
                irradiance += std::max(0.0f, (cosTheta * cosThetaLight) / (distanceToLight * distanceToLight));

            }
        }
    }
    float radiance = 250.0f;
    irradiance = (irradiance * scene.lights[0].area * radiance) / (samples * M_PI);

    return irradiance;
}


colorDBL Camera::traceRay(const Ray &ray, const Scene &scene, int depth) const {

    const int maxDepth = 5;
    if (depth > maxDepth) {
        return colorDBL(0.0, 0.0, 0.0);
    }

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

    const float EPSILON = 0.0001f;

    //return the color of the hit polygon
    if(hit_polygon) {
        float irradiance = calculateDirectLight(hit_point, hit_polygon->getNormal(), scene);
        colorDBL surfaceColor = hit_polygon->getColor();

        //TODO: Implement ray tracing for diffuse materials?

        if(hit_polygon->getMaterial() > 0.0f) {
            glm::vec3 normal = hit_polygon->getNormal();
            glm::vec3 ray_direction = ray.getDirection();
            glm::vec3 reflection_direction = ray_direction - 2.0f * glm::dot(ray_direction, normal) * normal;

            glm::vec3 offset = hit_point + normal * EPSILON;

            Ray reflection_ray(offset, offset + reflection_direction, hit_polygon->getColor());
            colorDBL reflected_color = traceRay(reflection_ray, scene, depth + 1);
            return (1.0f - hit_polygon->getMaterial()) * hit_polygon->getColor() + hit_polygon->getMaterial() * reflected_color;
        }

        // std::cout << "Direct light: R=" << directLight.r() << ", G=" << directLight.g() << ", B=" << directLight.b() << std::endl;
        colorDBL finalColor = surfaceColor * irradiance;

        return finalColor;
    }
    
    //else return black
    return colorDBL(0.0,0.0,0.0);
}



void Camera::render(const std::string& filename, const Scene& scene, int depth)  {
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Ray ray = createRay(i, j);
            pixels[j][i] = traceRay(ray,scene,depth);
        }
    }

    // Find the maximum color value
    double max_value = 0;
    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            max_value = std::max({max_value, pixel.r(), pixel.g(), pixel.b()});
        }
    }

    // Normalize and write to file
    std::ofstream out(filename, std::ios::binary);
    out << "P6\n" << width << " " << height << "\n255\n";

    for (const auto& row : pixels) {
        for (const auto& pixel : row) {
            // Check if max_value is greater than a small epsilon to avoid division by zero
            if (max_value > 1e-6) {
                char r = static_cast<char>(std::min(255.0, pixel.r() / max_value * 255));
                char g = static_cast<char>(std::min(255.0, pixel.g() / max_value * 255));
                char b = static_cast<char>(std::min(255.0, pixel.b() / max_value * 255));
                out.write(&r, 1);
                out.write(&g, 1);
                out.write(&b, 1);
            } else {
                // If max_value is essentially zero, write black pixels
                char zero = 0;
                out.write(&zero, 1);
                out.write(&zero, 1);
                out.write(&zero, 1);
            }
        }
    }
}


