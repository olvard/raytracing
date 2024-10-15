//
// Created by Oliver Lundin on 2024-10-15.
//

#ifndef MATERIAL_H
#define MATERIAL_H



class Material {
public:
    enum MaterialType {
        DIFFUSE,
        MIRROR,
        GLASS
    };

    // Constructor
    explicit Material(MaterialType type) : type(type) {}

    // get type
    MaterialType getType() const { return type; }


private:
    MaterialType type;

};



#endif //MATERIAL_H
