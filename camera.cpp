//
// Created by Oliver Lundin on 2024-09-10.
//

#include "camera.h"
#include <vector>
#include <fstream>
#include <future>
#include <iostream>
#include <glm/glm.hpp>
#include <thread>
#include <mutex>

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
    float irradiance = 0.0f;
    const int samples = 4;

    for(const auto& light : scene.lights) {
        for(int i = 0; i < samples; i++) {
            glm::vec3 pointOnLight = light.getRandomPoint();

            // Calculate the direction from hit point to light
            glm::vec3 direction = pointOnLight - hitPoint;
            float distanceToLight = glm::length(direction);
            direction = glm::normalize(direction);

            float cosTheta = glm::dot(hitPointNormal, direction);
            float cosThetaLight = glm::dot(-light.normal, direction);

              // Create shadow ray with normalized direction
            Ray shadowRay(hitPoint + hitPointNormal * 0.001f, direction);
            bool inShadow = false;

            for(const auto& shape : scene.shapes) {
                float t;
                glm::vec3 intersectionPoint;
                // Check if intersection distance is less than distance to light
                if(shape->intersect(shadowRay, t, intersectionPoint) && t < distanceToLight - 0.001f) {
                    inShadow = true;
                    break;
                }
            }

            if (!inShadow && cosTheta > 0.0f && cosThetaLight > 0.0f) {
                irradiance += (cosTheta * cosThetaLight) / (distanceToLight * distanceToLight);
            }
        }
    }

    float radiance = 8500.0f;
    irradiance = (irradiance * scene.lights[0].area * radiance) / (samples * M_PI);

    return irradiance;
}

float getRandom() {
    thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

colorDBL Camera::traceRay(Ray &ray, const Scene &scene, int depth) const {

    const int maxDepth = 3;
    if (depth > maxDepth) {
        return colorDBL(0.0, 0.0, 0.0);
    }

    float closest_t = std::numeric_limits<float>::max();
    const Shape* hit_shape = nullptr;
    glm::vec3 hit_point;

    //Loop through the polygons in the scene
    for (const auto& shape : scene.shapes) {
        float t;
        glm::vec3 intersectionPoint;
        if (shape->intersect(ray, t, intersectionPoint)) {
            if(t < closest_t) {
                closest_t = t;
                hit_shape = shape.get();
                hit_point = intersectionPoint;
            }
        }
    }

    const float EPSILON = 0.0001f;

    //return the color of the hit polygon
    if(hit_shape) {
        glm::vec3 normal = hit_shape->getNormal(hit_point);
        Material::MaterialType material_type = hit_shape->getMaterial().getType();

        switch (material_type) {

            default: {
                return colorDBL(0.0, 0.0, 0.0);
            }

            case Material::LIGHT: {
                return hit_shape->getColor() * 500.0f;
            }

            // Mirror
            case Material::MIRROR: {
                //glm::vec3 normal = hit_shape->getNormal(hit_point);
                glm::vec3 ray_direction = ray.getDirection();
                glm::vec3 reflection_direction = ray_direction - 2.0f * glm::dot(ray_direction, normal) * normal;

                glm::vec3 offset = hit_point + normal * EPSILON;

                Ray reflection_ray(offset, offset + reflection_direction, hit_shape->getColor());
                colorDBL reflected_color = traceRay(reflection_ray, scene, depth + 1);
                return reflected_color;
            }

            // Diffuse
            case Material::DIFFUSE: {
               // Generate random direction in hemisphere for diffuse reflection
                const int numSamples = 4;  // Number of random samples for diffuse reflection
                colorDBL accumulated_color(0.0, 0.0, 0.0);

                for(int i = 0; i < numSamples; i++) {
                    // Generate random direction in hemisphere
                    float theta = 2.0f * M_PI * getRandom();
                    float phi = acos(sqrt(getRandom()));

                    // Convert spherical to cartesian coordinates
                    glm::vec3 random_direction(
                        sin(phi) * cos(theta),
                        sin(phi) * sin(theta),
                        cos(phi)
                    );

                    // Create orthonormal basis around normal
                    glm::vec3 w = normal;
                    glm::vec3 u = glm::normalize(glm::cross(
                        (std::abs(w.x) > 0.1f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f)),
                        w));
                    glm::vec3 v = glm::cross(w, u);

                    // Transform random direction to world space
                    glm::vec3 world_direction =
                        u * random_direction.x +
                        v * random_direction.y +
                        w * random_direction.z;

                    glm::vec3 offset = hit_point + normal * EPSILON;

                    // Create and link new ray
                    auto diffuse_ray = std::make_shared<Ray>(
                        offset,
                        offset + world_direction,
                        hit_shape->getColor()
                    );
                    ray.setNextRay(diffuse_ray);

                    // Trace the ray and accumulate color
                    colorDBL bounce_color = traceRay(*diffuse_ray, scene, depth + 1);
                    float cosTheta = glm::dot(world_direction, normal);

                    // Accumulate color using BRDF (lambertian) and cosine term
                    accumulated_color = accumulated_color +
                        (bounce_color * hit_shape->getColor() * cosTheta);
                }

                // Calculate direct lighting
                float direct_irradiance = calculateDirectLight(hit_point, normal, scene);
                colorDBL direct_light = hit_shape->getColor() * direct_irradiance;

                // Combine direct and indirect lighting
                return direct_light + (accumulated_color * (1.0f / numSamples));
            }
        }

    }

    //else return black
    return colorDBL(0.0,0.0,0.0);
}

void Camera::renderSegment(int startRow, int endRow, const Scene& scene, int depth) {
    for(int j = startRow; j < endRow; j++) {
        for(int i = 0; i < width; i++) {
            Ray ray = createRay(i, j);
            pixels[j][i] = traceRay(ray, scene, depth);
        }
    }
}

void Camera::render(const std::string& filename, const Scene& scene, int depth) {
    // Determine number of threads (use hardware concurrency or fall back to 4)
    unsigned int numThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads: " << numThreads << std::endl;
    //numThreads = numThreads > 0 ? numThreads : 4;

    // Calculate rows per thread
    int rowsPerThread = height / numThreads;
    std::vector<std::thread> threads;

    // Create and launch threads
    for(unsigned int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? height : (i + 1) * rowsPerThread;

        threads.emplace_back(&Camera::renderSegment, this, startRow, endRow,
                               std::ref(scene), depth);
    }

    // Wait for all threads to complete
    for(auto& thread : threads) {
        thread.join();
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
            if (max_value > 1e-6) {
                char r = static_cast<char>(std::min(255.0, pixel.r()));
                char g = static_cast<char>(std::min(255.0, pixel.g()));
                char b = static_cast<char>(std::min(255.0, pixel.b()));
                out.write(&r, 1);
                out.write(&g, 1);
                out.write(&b, 1);
            } else {
                char zero = 0;
                out.write(&zero, 1);
                out.write(&zero, 1);
                out.write(&zero, 1);
            }
        }
    }
}


