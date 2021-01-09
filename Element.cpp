//
// Created by ofir on 09/01/2021.
//

#include "Element.h"

//constructors
Element::Element(float height, int size) {
    this->_height = height;
    this->_size = size;
}

//getters
float Element::getHeight() const {
    return _height;
}

int Element::getSize() const {
    return this->_size;
}
