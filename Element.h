//
// Created by ofir on 09/01/2021.
//

#pragma once

class Element
{
protected:
    float _height;
    int _size;

public:
    Element(float height, int size);

    virtual float calcDistance(Element* other) =0;//abstract function

    float getHeight() const;
    int getSize() const;

};


