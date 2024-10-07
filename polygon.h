//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef POLYGON_H
#define POLYGON_H

#include <glm/glm.hpp>
#include <vector>
#include "colorDBL.h"
#include "ray.h"

class Polygon {

public:

    Polygon(const std::vector<glm::vec3>& vertices, const colorDBL& col, float material) : vertices(vertices), color(col), material(material)
    {}

    virtual ~Polygon() = default;

    const std::vector<glm::vec3>& getVertices() const { return vertices; }

    const colorDBL& getColor() const { return color; }

    const float getMaterial() const { return material; }

    glm::vec3 getNormal() const;

    virtual bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const = 0;

protected:
    std::vector<glm::vec3> vertices;
    colorDBL color;
    float material;
};

class Rectangle : public Polygon {
public:
    Rectangle(const std::vector<glm::vec3>& vertices, const colorDBL& col, float material);
    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
};

class Triangle : public Polygon {
public:
    Triangle(const std::vector<glm::vec3>& vertices, const colorDBL& col, float material);
    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;

};




#endif //POLYGON_H
