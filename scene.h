//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "polygon.h"


class Scene {
public:
    std::vector<Polygon> polygons;  // Collection of polygons

   Scene() = default;

    // Add a polygon to the scene
    void addPolygon(const Polygon& polygon) {
        polygons.push_back(polygon);
    }



};

#endif //SCENE_H