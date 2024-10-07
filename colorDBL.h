//
// Created by Oliver Lundin on 2024-09-10.
//

#ifndef COLORDBL_H
#define COLORDBL_H

#include <glm/glm.hpp>

class colorDBL {
public:
    // Constructor
    explicit colorDBL(double r = 0.0, double g = 0.0, double b = 0.0) : color(r, g, b) {}

    // Getters
    double r() const { return color.r; }
    double g() const { return color.g; }
    double b() const { return color.b; }

    // Operators
    colorDBL operator+(const colorDBL& c) const {
        return colorDBL(r() + c.r(), g() + c.g(), b() + c.b());
    }

    // multiplication with float operator
    colorDBL operator*(double f) const {
        return colorDBL(r() * f, g() * f, b() * f);
    }

    // addition with float operator
    colorDBL operator+(double f) const {
        return colorDBL(r() + f, g() + f, b() + f);
    }

    // multiplication with colorDBL operator
    colorDBL operator*(const colorDBL& c) const {
        return colorDBL(r() * c.r(), g() * c.g(), b() * c.b());
    }

    // += operator
    colorDBL& operator+=(const colorDBL& other) {
        color.r += other.r();
        color.g += other.g();
        color.b += other.b();
        return *this;
    }

    // division with float operator
    colorDBL operator/(float f) const {
        return colorDBL(r() / f, g() / f, b() / f);
    }

    // Friend function for float * colorDBL
    friend colorDBL operator*(float f, const colorDBL& c) {
        return colorDBL(c.r() * f, c.g() * f, c.b() * f);
    }


    // Friend function for double * colorDBL
    friend colorDBL operator*(double f, const colorDBL& c) {
        return c * f; // Reuse the member function
    }

    // Convert color to glm::vec3
    glm::vec3 toVec3() const { return color; }

protected:
    glm::vec3 color;



};
#endif //COLORDBL_H
