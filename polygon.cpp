//
// Created by Oliver Lundin on 2024-09-10.
//
#include "polygon.h"

Rectangle::Rectangle(const std::vector<glm::vec3> &vertices, const colorDBL &col) : Polygon(vertices, col) {
    if(vertices.size() != 4) {
        throw std::invalid_argument("Rectangle must have 4 vertices");
    }
}

bool Rectangle::intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const {
    glm::vec3 normal = getNormal();
    float denominator = glm::dot(normal, ray.getDirection());

    if (std::abs(denominator) > 1e-6) {
        glm::vec3 v0 = vertices[0];
        t = glm::dot(v0 - ray.ps, normal) / denominator;

        if (t >= 0) {
            intersectionPoint = ray.pointAt(t);
            glm::vec3 v1 = vertices[1], v2 = vertices[2];
            glm::vec3 edge1 = v1 - v0, edge2 = v2 - v0;
            glm::vec3 vp = intersectionPoint - v0;

            float a = glm::dot(vp, edge1) / glm::dot(edge1, edge1);
            float b = glm::dot(vp, edge2) / glm::dot(edge2, edge2);

            return (a >= 0 && a <= 1 && b >= 0 && b <= 1);
        }
    }
    return false;
}

Triangle::Triangle(const std::vector<glm::vec3> &vertices, const colorDBL &col) : Polygon(vertices, col) {
    if(vertices.size() != 3) {
        throw std::invalid_argument("Triangle must have 3 vertices");
    }
}

bool Triangle::intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const {
    const float EPSILON = 0.0000001;
    glm::vec3 vertex0 = vertices[0];
    glm::vec3 vertex1 = vertices[1];
    glm::vec3 vertex2 = vertices[2];
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    // Step 1: Calculate two edges of the triangle
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;

    // Step 2: Calculate the cross product of ray direction and one edge
    h = glm::cross(ray.getDirection(), edge2);

    // Step 3: Calculate the determinant
    // If the determinant is near zero, ray lies in the plane of the triangle
    a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;  // Ray is parallel to the triangle

    // Step 4: Calculate u parameter and test bounds
    f = 1.0 / a;
    s = ray.ps - vertex0;  // Vector from vertex0 to ray origin
    u = f * glm::dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;  // Intersection point is outside the triangle

    // Step 5: Calculate v parameter and test bounds
    q = glm::cross(s, edge1);
    v = f * glm::dot(ray.getDirection(), q);
    if (v < 0.0 || u + v > 1.0)
        return false;  // Intersection point is outside the triangle

    // Step 6: Calculate t, the distance from ray origin to intersection point
    t = f * glm::dot(edge2, q);

    // Step 7: Check if the intersection point is in front of the ray origin
    if (t > EPSILON) {
        // Calculate the intersection point
        intersectionPoint = ray.pointAt(t);
        return true;
    }

    // Line intersects the plane of the triangle, but not the triangle itself
    return false;
}






