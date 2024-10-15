//
// Created by Oliver Lundin on 2024-10-15.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include "colorDBL.h"
#include "ray.h"
#include <vector>
#include "material.h"

// Abstract base class for all shapes
// shape.h
class Shape {
public:
    Shape(const colorDBL& color, Material material) : color(color), material(material) {}
    virtual ~Shape() = default;

    virtual bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const = 0;
    virtual glm::vec3 getNormal(glm::vec3& point) const = 0;

    Material getMaterial() const { return material; }
    const colorDBL& getColor() const { return color; }

protected:
    colorDBL color;
    Material material;
};

// polygon.h
class Rectangle : public Shape {
public:
    Rectangle(const std::vector<glm::vec3>& vertices, const colorDBL& col, Material material)
        : Shape(col, material), vertices(vertices) {}

    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
    glm::vec3 getNormal(glm::vec3& point) const override;

private:
    std::vector<glm::vec3> vertices;
};

class Triangle : public Shape {
public:
    Triangle(const std::vector<glm::vec3>& vertices, const colorDBL& col, Material material)
        : Shape(col, material), vertices(vertices) {}

    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
    glm::vec3 getNormal(glm::vec3& point) const override;

private:
    std::vector<glm::vec3> vertices;
};

// sphere.h
class Sphere : public Shape {
public:
    Sphere(glm::vec3 center, float radius, const colorDBL& color, Material material)
        : Shape(color, material), center(center), radius(radius) {}

    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
    glm::vec3 getNormal(glm::vec3& point) const override;

private:
    glm::vec3 center;
    float radius;
};

#endif // SHAPE_H
