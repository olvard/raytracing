
//
// Created by Oliver Lundin on 2024-09-10.
//

#include "shape.h"

glm::vec3 Rectangle::getNormal(glm::vec3& point) const {
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    return glm::normalize(glm::cross(edge1, edge2));
}

glm::vec3 Triangle::getNormal(glm::vec3& point) const {
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    return glm::normalize(glm::cross(edge1, edge2));
}

/*Rectangle::Rectangle(const std::vector<glm::vec3> &vertices, const colorDBL &col, float material) : Shape(col, material) {
    if(vertices.size() != 4) {
        throw std::invalid_argument("Rectangle must have 4 vertices");
    }
}*/

bool Rectangle::intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const {
    glm::vec3 normal = getNormal(intersectionPoint);
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

/*Triangle::Triangle(const std::vector<glm::vec3> &vertices, const colorDBL &col, float material) : Shape(col, material) {
    if(vertices.size() != 3) {
        throw std::invalid_argument("Triangle must have 3 vertices");
    }
}*/

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


// intersection method
bool Sphere::intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const {
    // Vector from ray origin to sphere center
    glm::vec3 SC = ray.ps - center;

    // Coefficients for the quadratic equation
    float c1 = glm::dot(ray.getDirection(), ray.getDirection());  // c1 = D^2
    float c2 = 2.0f * glm::dot(ray.getDirection(), SC);      // c2 = 2 * D * (S - C)
    float c3 = glm::dot(SC, SC) - radius * radius;      // c3 = (S - C)^2 - r^2

    // Discriminant of the quadratic equation
    float discriminant = c2 * c2 - 4.0f * c1 * c3;

    // No intersection if the discriminant is negative
    if (discriminant < 0.0f) {
        return false; // No intersection
    }

    // Compute the two possible values of t (time along the ray)
    float sqrtDiscriminant = std::sqrt(discriminant);
    float t1 = (-c2 - sqrtDiscriminant) / (2.0f * c1);
    float t2 = (-c2 + sqrtDiscriminant) / (2.0f * c1);

    // Select the smallest positive t value (if any)
    if (t1 >= 0.0f) {
        t = t1; // The first intersection point
    } else if (t2 >= 0.0f) {
        t = t2; // The second intersection point
    } else {
        return false; // Both t1 and t2 are negative, meaning the intersection is behind the ray
    }

    // Compute the intersection point using the ray equation: P = S + t * D
    intersectionPoint = ray.ps + t * ray.getDirection();

    return true; // Intersection found
}

// get normal
glm::vec3 Sphere::getNormal(glm::vec3& point) const {

    return glm::normalize(point - center);

}
