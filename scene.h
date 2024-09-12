//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>

#include "camera.h"
#include "polygon.h"


class Scene {
public:
    std::vector<Polygon> polygons;  // Collection of polygons
    std::vector<Camera> cameras;

   Scene() = default;

    // Add a polygon to the scene
    void addPolygon(const Polygon& polygon) {
        polygons.push_back(polygon);
    }

    // Add a room to the scene
    void addRoom();

    // Add a camera to the scene
    void addCamera(const Camera& camera) {
        cameras.push_back(camera);
    }



};

#endif //SCENE_H
