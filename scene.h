//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "light.h"
#include "shape.h"




class Scene {
public:
    std::vector<std::unique_ptr<Shape>> shapes;
    std::vector<Light> lights;


   Scene() = default;

    // Add a shape to the scene (polygon or sphere)
    void addShape(std::unique_ptr<Shape> shape) {
        shapes.push_back(std::move(shape));
    }

    // Add a polygon to the scene (wraps addShape)


    // Add a sphere to the scene (wraps addShape)
    void addSphere(const glm::vec3& center, float radius, const colorDBL& color, Material material) {
        shapes.push_back(std::make_unique<Sphere>(center, radius, color, material));
    }

    // Add a tetrahedron to the scene (similar to Polygon or as another Shape subclass)
    void addTetrahedron(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const colorDBL& color, Material material);


    // Add a room to the scene
    void addRoom();


};

#endif //SCENE_H
