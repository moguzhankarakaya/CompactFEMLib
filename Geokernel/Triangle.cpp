//
// Created by oguzhan on 16.06.18.
//

#include <cmath>
#include <iostream>
#include "Triangle.h"
#include "../Utilities/Bithacks.h"
#include "../Utilities/Constants.h"

Geokernel::Triangle::Triangle()
{
    _vertices[0].set_coordinates(0,0);
    _vertices[1].set_coordinates(2,0);
    _vertices[2].set_coordinates(1,1);
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);

}

Geokernel::Triangle::Triangle(const Geokernel::Types::VertexTrioRef vertexSet, const Geokernel::Types::EdgeTrioRef edgeSet)
{
    _vertices = vertexSet;
    _edges = edgeSet;

    calculate_area();
}

Geokernel::Triangle::Triangle(const Geokernel::Types::VertexTrioRef vertexSet)
{
    _vertices = vertexSet;
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);

    calculate_area();
}

Geokernel::Triangle::Triangle(const Geokernel::Types::CoordinateTrioRef coordinateSet)
{
    _vertices[0].set_coordinates(coordinateSet[0]);
    _vertices[1].set_coordinates(coordinateSet[1]);
    _vertices[2].set_coordinates(coordinateSet[2]);
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);

    calculate_area();
}

Geokernel::Triangle::Triangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
{
    _vertices[0] = vertex1;
    _vertices[1] = vertex2;
    _vertices[2] = vertex3;
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);

    calculate_area();
}

Geokernel::Triangle::Triangle(const Vertex::Coordinate& coordinate1,
                              const Vertex::Coordinate& coordinate2,
                              const Vertex::Coordinate& coordinate3)
{
    _vertices[0].set_coordinates(coordinate1);
    _vertices[1].set_coordinates(coordinate2);
    _vertices[2].set_coordinates(coordinate3);
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);

    calculate_area();
}

Geokernel::Triangle::Triangle(const Geokernel::Triangle& rectangle)
{
    _vertices = rectangle.get_vertices();
    _edges = rectangle.get_edges();

    calculate_area();
}

Geokernel::Triangle::~Triangle() = default;

Geokernel::Types::VertexTrio Geokernel::Triangle::get_vertices() const
{
    return _vertices;
}

Geokernel::Types::EdgeTrio Geokernel::Triangle::get_edges() const
{
    return _edges;
}

void Geokernel::Triangle::get_vector_vertex(Geokernel::Types::VertexContainerRef container)
{

    for(const auto &it : _vertices)
    {
        container.push_back(it);
    }

}

void Geokernel::Triangle::set_vertices(const Geokernel::Types::VertexTrioRef vertexSet)
{
    _vertices = vertexSet;
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[0]);;

    calculate_area();
}

void Geokernel::Triangle::set_edges(const Geokernel::Types::EdgeTrioRef edgeSet)
{
    //Assuming edges are order in clockwise orientation along with vertices
    _edges = edgeSet;
    _vertices[0] = _edges[0].get_vertices()[0];
    _vertices[1] = _edges[1].get_vertices()[0];
    _vertices[2] = _edges[2].get_vertices()[0];

    calculate_area();
}

void Geokernel::Triangle::calculate_area()
{
    _area = 0.5f * std::abs(_vertices[0].get_coordinates()._x * (_vertices[1].get_coordinates()._y -  \
                                                                 _vertices[2].get_coordinates()._y) + \
                            _vertices[1].get_coordinates()._x * (_vertices[2].get_coordinates()._y -  \
                                                                 _vertices[0].get_coordinates()._y) + \
                            _vertices[2].get_coordinates()._x * (_vertices[0].get_coordinates()._y -  \
                                                                 _vertices[1].get_coordinates()._y));
}

float Geokernel::Triangle::get_area() const
{
    return _area;
}

float Geokernel::Triangle::get_edge_length(int edgeNumber) const
{
    if(edgeNumber >= 0 && edgeNumber <= 2)
    {
        return _edges[edgeNumber].get_length();
    }
    else
    {
        throw "Invalid Triangle Edge Specification";
    }
}

bool Geokernel::Triangle::isInside(const Geokernel::Vertex &vertex)
{
    double area_1 = Triangle(_vertices[0], _vertices[1], vertex).get_area();

    double area_2 = Triangle(_vertices[0], _vertices[2], vertex).get_area();

    double area_3 = Triangle(_vertices[1], _vertices[2], vertex).get_area();

    double sum_of_areas = area_1 + area_2 + area_3;

    PrimaryUtilities::Tolerance<double> isEqual(GlobalConstants::INSIDE_TEST_PRECISION);

    isEqual.set_boundary(_area);

    return isEqual.check_value(sum_of_areas);
}

void Geokernel::Triangle::isInside(const Geokernel::Types::VertexContainerRef vertexContainer,
                                   std::vector<char>& checkList)
{

    for(auto it : vertexContainer)
    {
        checkList.emplace_back(isInside(it));
    }

}

void Geokernel::Triangle::print_stream_out()
{
    std::cout << "Triangle:" << std::endl;
    std::cout << "1. Edge: " << std::endl;
    _edges[0].print_stream_out();
    std::cout << "2. Edge: " << std::endl;
    _edges[1].print_stream_out();
    std::cout << "3. Edge: " << std::endl;
    _edges[2].print_stream_out();
}

Geokernel::Vertex Geokernel::Triangle::get_barycentric_point() const
{
    auto v1 = float(1./3);
    auto v2 = float(1./3);
    auto v3 = float(1./3);

    Geokernel::Vertex returnValue;

    Vertex::Coordinate t1(_vertices[0].get_coordinates());
    Vertex::Coordinate t2(_vertices[1].get_coordinates());
    Vertex::Coordinate t3(_vertices[2].get_coordinates());

    returnValue.set_coordinates(t1._x*v1 + t2._x*v2 +t3._x*v3,
                                t1._y*v1 + t2._y*v2 +t3._y*v3,
                                t1._z*v1 + t2._z*v2 +t3._z*v3);

    return returnValue;

}

Geokernel::Vertex Geokernel::Triangle::get_barycentric_point(float v1, float v2, float v3)
{
    if(v1 + v2 + v3 != 1.0) throw "Given Barycentric coordinates are not valid. Their sum should be equal to 1.0";

    Geokernel::Vertex returnValue;

    Vertex::Coordinate t1(_vertices[0].get_coordinates());
    Vertex::Coordinate t2(_vertices[1].get_coordinates());
    Vertex::Coordinate t3(_vertices[2].get_coordinates());

    returnValue.set_coordinates(t1._x*v1 + t2._x*v2 +t3._x*v3,
                                t1._y*v1 + t2._y*v2 +t3._y*v3,
                                t1._z*v1 + t2._z*v2 +t3._z*v3);

    return returnValue;

}
