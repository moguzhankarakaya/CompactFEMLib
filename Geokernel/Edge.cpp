//
// Created by oguzhan on 10.06.18.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include "Edge.h"
#include "../Utilities/Bithacks.h"

Geokernel::Edge::Edge() {

    _vertices[0].set_coordinates(0, 0);
    _vertices[1].set_coordinates(0, 0);
    _isSlopeSet = false;

}

Geokernel::Edge::Edge(const Geokernel::Vertex& a, const Geokernel::Vertex& b) {

    if (a < b)
    {
        _vertices[0] = a;
        _vertices[1] = b;
    }
    else
    {
        _vertices[0] = b;
        _vertices[1] = a;
    }
    calculate_slope();
    calculate_length();

}

Geokernel::Edge::Edge(const Geokernel::VertexPairRef vertexPair) {

    if(vertexPair[0] < vertexPair[1])
    {
        _vertices[0].set_coordinates(vertexPair[0].get_coordinates());
        _vertices[1].set_coordinates(vertexPair[1].get_coordinates());
    }
    else
    {
        _vertices[0].set_coordinates(vertexPair[1].get_coordinates());
        _vertices[1].set_coordinates(vertexPair[0].get_coordinates());
    }
    calculate_slope();
    calculate_length();

}

Geokernel::Edge::Edge(const Geokernel::Edge& edge) {

    _vertices[0] = edge.get_vertices()[0];
    _vertices[1] = edge.get_vertices()[1];
    for(const auto &it : edge.get_mid_vertices()){
        _midVertices.push_back(it);
    }
    calculate_slope();
    calculate_length();
}

Geokernel::Edge::~Edge() = default;


Geokernel::VertexPair Geokernel::Edge::get_vertices() const {

    return _vertices;

}

void Geokernel::Edge::set_vertices(const Geokernel::VertexPairRef vertexPair) {

    if(vertexPair[0] < vertexPair[1])
    {
        _vertices[0].set_coordinates(vertexPair[0].get_coordinates());
        _vertices[1].set_coordinates(vertexPair[1].get_coordinates());
    }
    else
    {
        _vertices[0].set_coordinates(vertexPair[1].get_coordinates());
        _vertices[1].set_coordinates(vertexPair[0].get_coordinates());
    }
    calculate_slope();
    calculate_length();

}


void Geokernel::Edge::set_vertices(const Geokernel::Vertex& a, const Geokernel::Vertex& b) {

    if (a < b)
    {
        _vertices[0] = a;
        _vertices[1] = b;
    }
    else
    {
        _vertices[0] = b;
        _vertices[1] = a;
    }
    calculate_slope();
    calculate_length();

}

void Geokernel::Edge::set_vertices(const Geokernel::Vertex::Coordinate& v1,
                                   const Geokernel::Vertex::Coordinate& v2) {

    if(v1 < v2)
    {
        _vertices[0].set_coordinates(v1);
        _vertices[1].set_coordinates(v2);
    }
    else
    {
        _vertices[0].set_coordinates(v2);
        _vertices[1].set_coordinates(v1);
    }
    calculate_slope();
    calculate_length();

};


Geokernel::VertexContainer Geokernel::Edge::get_mid_vertices() const
{

    return _midVertices;

}


size_t Geokernel::Edge::get_num_of_mid_vertices() const {

    return _midVertices.size();

}


float Geokernel::Edge::get_slope() const {
    if(_isSlopeSet)
        return _slope;
    else
    {
        throw false;
    }
}

void Geokernel::Edge::calculate_slope(){

    try
    {
        float denum = (_vertices[1].get_coordinates()._x - _vertices[0].get_coordinates()._x);
        PrimaryUtilities::Tolerance<float> tolerance(1e-8);
        tolerance.set_boundary(0);
        if(tolerance.check_value(denum))
        {
            throw false;
        }

        float num = (_vertices[1].get_coordinates()._y - _vertices[0].get_coordinates()._y);

        _slope = num / denum;
        _isSlopeSet = true;
    }
    catch (bool slopeSet)
    {
        _isSlopeSet = slopeSet;
    }
}

float Geokernel::Edge::get_length() const {

    return _length;

}

void Geokernel::Edge::calculate_length() {

    float len_x = _vertices[1].get_coordinates()._x - _vertices[0].get_coordinates()._x;
    float len_y = _vertices[1].get_coordinates()._y - _vertices[0].get_coordinates()._y;
    _length = std::sqrt(len_x*len_x + len_y*len_y);

}

void Geokernel::Edge::divide_edge(int numOfDivisorPoints) {
    if (_midVertices.empty())
    {
        float x_init = _vertices[0].get_coordinates()._x;

        float y_init = _vertices[0].get_coordinates()._y;

        float x_step = (_vertices[1].get_coordinates()._x \
                     - _vertices[0].get_coordinates()._x ) / (numOfDivisorPoints + 1);
        float y_step = (_vertices[1].get_coordinates()._y \
                     - _vertices[0].get_coordinates()._y ) / (numOfDivisorPoints + 1);
        for(int i = 0; i < numOfDivisorPoints; i++)
        {
            Vertex newMidVertex(x_init + (i + 1) * x_step, y_init + (i + 1) * y_step);
            _midVertices.push_back(newMidVertex);
        }
    }
    else
    {
        float x_init = _vertices[0].get_coordinates()._x;

        float y_init = _vertices[0].get_coordinates()._y;

        float x_step = (_midVertices[0].get_coordinates()._x \
                     - _vertices[0].get_coordinates()._x ) / (numOfDivisorPoints + 1);
        float y_step = (_midVertices[0].get_coordinates()._y \
                     - _vertices[0].get_coordinates()._y ) / (numOfDivisorPoints + 1);
        for(int i = 0; i < numOfDivisorPoints; i++)
        {
            Vertex newMidVertex(x_init + (i + 1) * x_step, y_init + (i + 1) * y_step);
            _midVertices.push_back(newMidVertex);
        }
    }

    std::sort(_midVertices.begin(), _midVertices.end());

}

void Geokernel::Edge::divide_edge(const Geokernel::Vertex& vertex) {

    if (this->is_on_edge(vertex))
    {
        _midVertices.push_back(vertex);
    }

    else
    {
        throw "Vertex is not on the edge!";
    }

    std::sort(_midVertices.begin(), _midVertices.end());
}

void Geokernel::Edge::print_stream_out() {

    std::cout << "Edge: " << std::endl;
    std::cout << "1. Vertex: " << std::endl;
    _vertices[0].print_stream_out();
    std::cout << "2. Vertex: " << std::endl;
    _vertices[1].print_stream_out();

}

bool Geokernel::Edge::is_on_edge(const Geokernel::Vertex &vertex) {
    if(_isSlopeSet)
    {
        float a = this->get_slope();

        if( a != 0 )
        {
            float b = _vertices[0].get_coordinates()._y - a * _vertices[0].get_coordinates()._x;

            float _isY = a * vertex.get_coordinates()._x + b;

            return _isY == vertex.get_coordinates()._y &&
                    vertex.get_coordinates()._x < _vertices[1].get_coordinates()._x &&
                    vertex.get_coordinates()._y < _vertices[1].get_coordinates()._y &&
                    vertex.get_coordinates()._x > _vertices[0].get_coordinates()._x &&
                    vertex.get_coordinates()._y > _vertices[0].get_coordinates()._y;

        }
        else
        {
            return (vertex.get_coordinates()._y == _vertices[0].get_coordinates()._y) &&
                   (vertex.get_coordinates()._x <  _vertices[1].get_coordinates()._x) &&
                   (vertex.get_coordinates()._x >  _vertices[0].get_coordinates()._x);
        }
    }
    else
    {
        return (vertex.get_coordinates()._x == _vertices[0].get_coordinates()._x) &&
               (vertex.get_coordinates()._y <  _vertices[1].get_coordinates()._y) &&
               (vertex.get_coordinates()._y >  _vertices[0].get_coordinates()._y);

    }
}

