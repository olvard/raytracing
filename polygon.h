//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef POLYGON_H
#define POLYGON_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <vector>
#include "colorDBL.h"
#include "ray.h"

class Polygon {

public:

    Polygon(const std::vector<glm::vec3>& vertices, const colorDBL& col) : vertices(vertices), color(col)
    {}

    virtual ~Polygon() = default;

    const std::vector<glm::vec3>& getVertices() const { return vertices; }

    const colorDBL& getColor() const { return color; }

    glm::vec3 getNormal() const {
        return glm::triangleNormal(vertices[0], vertices[1], vertices[2]);
    }

    virtual bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const = 0;

protected:
    std::vector<glm::vec3> vertices;
    colorDBL color;
};

class Rectangle : public Polygon {
public:
    Rectangle(const std::vector<glm::vec3>& vertices, const colorDBL& col);
    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
};

class Triangle : public Polygon {
public:
    Triangle(const std::vector<glm::vec3>& vertices, const colorDBL& col);
    bool intersect(const Ray& ray, float& t, glm::vec3& intersectionPoint) const override;
};


#endif //POLYGON_H
