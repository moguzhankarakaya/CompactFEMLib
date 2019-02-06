//
// Created by oguzhan on 10.06.18.
//

#include <functional>
#include <iostream>
#include "Vertex.h"
#include "../Utilities/Bithacks.h"

Geokernel::Vertex::Vertex()
{

    _coordinate = Coordinate(0, 0, 0);

}

Geokernel::Vertex::Vertex(float x, float y) : _coordinate(x, y, 0)
{

}

Geokernel::Vertex::Vertex(float x, float y, float z) : _coordinate(x, y, z)
{

}

Geokernel::Vertex::Vertex(const Vertex& vertex)
{

    _coordinate = Coordinate(vertex.get_coordinates());

}

Geokernel::Vertex::Vertex(const Coordinate& coordinate)
{

    _coordinate = coordinate;

}

Geokernel::Vertex& Geokernel::Vertex::operator=(const Geokernel::Vertex& rhs) {

    this->set_coordinates(rhs.get_coordinates());
    return *this;

}

bool Geokernel::Vertex::operator<(const Geokernel::Vertex& rhs) const
{
    if (_coordinate._y != rhs.get_coordinates()._y)
        return _coordinate._y < rhs.get_coordinates()._y;
    return _coordinate._x < rhs.get_coordinates()._x;
}

Geokernel::Vertex::~Vertex() = default;


const Geokernel::Vertex::Coordinate& Geokernel::Vertex::get_coordinates() const {

    return _coordinate;

}

void Geokernel::Vertex::set_coordinates(const Geokernel::Vertex::Coordinate& coordinate) {

    Vertex::_coordinate = coordinate;

}

void Geokernel::Vertex::set_coordinates(float x, float y) {

    _coordinate = Vertex::Coordinate(x, y, 0);

}

void Geokernel::Vertex::set_coordinates(float x, float y, float z) {

    _coordinate = Vertex::Coordinate(x, y, z);

}

void Geokernel::Vertex::print_stream_out() {

    std::cout << "Vertex: " << std::endl;
    std::cout << "Coordinates: " << std::endl;
    std::cout << "x: " << _coordinate._x << std::endl;
    std::cout << "y: " << _coordinate._y << std::endl;
    std::cout << "z: " << _coordinate._z << std::endl;

}
