//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "light.h"
#include "polygon.h"


class Scene {
public:
    std::vector<std::unique_ptr<Polygon>> polygons;
    std::vector<Light> lights;


   Scene() = default;

    // Add a polygon to the scene
    void addPolygon(std::unique_ptr<Polygon> polygon) {
        polygons.push_back(std::move(polygon));
    }

    // Add a room to the scene
    void addRoom();


};

#endif //SCENE_H
