//
// Created by Oliver Lundin on 2024-09-26.
//

#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <random>
#include <glm/glm.hpp>
#include <__random/random_device.h>

#include "colorDBL.h"



class Light {
public:
    glm::vec3 v1,v2,v3,v4;
    glm::vec3 normal;
    colorDBL intensity;
    float area;

    Light(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const colorDBL& intensity) :
    v1(v1), v2(v2), v3(v3), v4(v4), intensity(intensity) {
        glm::vec3 e1 = v2 - v1;
        glm::vec3 e2 = v3 - v1;
        normal = normalize(cross(e1, e2));
        if (normal.z > 0) {
            normal = -normal;
        }
        area = length(e1) * length(e2);
    }

    glm::vec3 getRandomPoint() const {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 1.0);

        float s = dis(gen);
        float t = dis(gen);
        return v1 + s * (v2 - v1) + t * (v3 - v1);
    }

    void debugPrint() const {
        std::cout << "Light properties:" << std::endl;
        std::cout << "Normal: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Intensity: R=" << intensity.r() << ", G=" << intensity.g() << ", B=" << intensity.b() << std::endl;
    }


};



#endif //LIGHT_H
