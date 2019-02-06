//
// Created by oguzhan on 10.06.18.
//

#include <iostream>
#include "Rectangle.h"
#include "Triangle.h"
#include "ConvexHull.h"
#include "../Utilities/Bithacks.h"
#include "../Utilities/Constants.h"

Geokernel::Rectangle::Rectangle()
{

    _vertices[0].set_coordinates(0,0);
    _vertices[1].set_coordinates(1,0);
    _vertices[2].set_coordinates(1,1);
    _vertices[3].set_coordinates(0,1);
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Types::VertexQuadRef vertexSet, const Types::EdgeQuadRef edgeSet)
{

    _vertices = vertexSet;
    _edges = edgeSet;

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Types::VertexQuadRef vertexSet)
{
    ConvexHull convexHull(vertexSet);
    convexHull.calculate_convex_hull();
    int idx = 0;
    for(auto it: convexHull.get_convex_hull())
    {
        _vertices[idx] = it;
        idx++;
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Types::CoordinateQuadRef coordinateSet)
{
    ConvexHull convexHull(coordinateSet);
    convexHull.calculate_convex_hull();
    int idx = 0;
    for(auto it: convexHull.get_convex_hull())
    {
        _vertices[idx] = it;
        idx++;
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Types::VertexPairRef vertexPair)
{
    if(vertexPair[0] < vertexPair[1])
    {
        _vertices[0] = vertexPair[0];
        _vertices[1] = Vertex(vertexPair[1].get_coordinates()._x,
                              vertexPair[0].get_coordinates()._y);
        _vertices[2] = vertexPair[1];
        _vertices[3] = Vertex(vertexPair[0].get_coordinates()._x,
                              vertexPair[1].get_coordinates()._y);
    }
    else
    {
        _vertices[0] = vertexPair[1];
        _vertices[1] = Vertex(vertexPair[0].get_coordinates()._x,
                              vertexPair[1].get_coordinates()._y);
        _vertices[2] = vertexPair[0];
        _vertices[3] = Vertex(vertexPair[1].get_coordinates()._x,
                              vertexPair[0].get_coordinates()._y);
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Types::CoordinatePairRef coordinatePair)
{
    if(coordinatePair[0] < coordinatePair[1])
    {
        _vertices[0].set_coordinates(coordinatePair[0]);
        _vertices[1].set_coordinates(coordinatePair[1]._x, coordinatePair[0]._y);
        _vertices[2].set_coordinates(coordinatePair[1]);
        _vertices[3].set_coordinates(coordinatePair[0]._x, coordinatePair[1]._y);
    }
    else
    {
        _vertices[0].set_coordinates(coordinatePair[1]);
        _vertices[1].set_coordinates(coordinatePair[0]._x, coordinatePair[1]._y);
        _vertices[2].set_coordinates(coordinatePair[0]);
        _vertices[3].set_coordinates(coordinatePair[1]._x, coordinatePair[0]._y);
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Vertex& vertex1, const Vertex& vertex2)
{
    if(vertex1 < vertex2)
    {
        _vertices[0] = vertex1;
        _vertices[1] = Vertex(vertex2.get_coordinates()._x,
                              vertex1.get_coordinates()._y);
        _vertices[2] = vertex2;
        _vertices[3] = Vertex(vertex1.get_coordinates()._x,
                              vertex2.get_coordinates()._y);
    }
    else
    {
        _vertices[0] = vertex2;
        _vertices[1] = Vertex(vertex1.get_coordinates()._x,
                              vertex2.get_coordinates()._y);
        _vertices[2] = vertex1;
        _vertices[3] = Vertex(vertex2.get_coordinates()._x,
                              vertex1.get_coordinates()._y);
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Vertex::Coordinate& coordinate1,
                                const Vertex::Coordinate& coordinate2)
{
    if(coordinate1 < coordinate2) {
        _vertices[0].set_coordinates(coordinate1);
        _vertices[1].set_coordinates(coordinate2._x, coordinate1._y);
        _vertices[2].set_coordinates(coordinate2);
        _vertices[3].set_coordinates(coordinate1._x, coordinate2._y);
    }
    else
    {
        _vertices[0].set_coordinates(coordinate2);
        _vertices[1].set_coordinates(coordinate1._x, coordinate2._y);
        _vertices[2].set_coordinates(coordinate1);
        _vertices[3].set_coordinates(coordinate2._x, coordinate1._y);
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

Geokernel::Rectangle::Rectangle(const Geokernel::Rectangle& rectangle)
{

    _vertices = rectangle.get_vertices();
    _edges = rectangle.get_edges();

    calculate_area();
}

Geokernel::Rectangle::~Rectangle() = default;


Geokernel::Types::VertexQuad Geokernel::Rectangle::get_vertices() const
{

    return _vertices;

}

Geokernel::Types::EdgeQuad Geokernel::Rectangle::get_edges() const
{

    return _edges;

}

void Geokernel::Rectangle::get_vector_vertex(Types::VertexContainerRef container)
{
    for(const auto &it : _vertices)
    {
        container.push_back(it);
    }

}

void Geokernel::Rectangle::set_vertices(const Types::VertexQuadRef vertexSet)
{
    ConvexHull convexHull(vertexSet);
    convexHull.calculate_convex_hull();
    int idx = 0;
    for(auto it: convexHull.get_convex_hull())
    {
        _vertices[idx] = it;
        idx++;
    }
    _edges[0].set_vertices(_vertices[0], _vertices[1]);
    _edges[1].set_vertices(_vertices[1], _vertices[2]);
    _edges[2].set_vertices(_vertices[2], _vertices[3]);
    _edges[3].set_vertices(_vertices[3], _vertices[0]);

    calculate_area();
}

bool Geokernel::Rectangle::isInside(const Geokernel::Vertex& vertex)
{
    double area_1 = Triangle(vertex, _vertices[0], _vertices[1]).get_area();
    double area_2 = Triangle(vertex, _vertices[1], _vertices[2]).get_area();
    double area_3 = Triangle(vertex, _vertices[2], _vertices[3]).get_area();
    double area_4 = Triangle(vertex, _vertices[3], _vertices[0]).get_area();

    double sum_of_areas = area_1 + area_2 + area_3 + area_4;

    PrimaryUtilities::Tolerance<double> isEqual(GlobalConstants::INSIDE_TEST_PRECISION);

    isEqual.set_boundary(_area);

    return isEqual.check_value(sum_of_areas);
}

void Geokernel::Rectangle::isInside(const Types::VertexContainerRef vertexContainer,
                                    std::vector<char>& checkList)
{

    for(const auto &it : vertexContainer)
    {
        checkList.push_back(isInside(it));
    }

}

void Geokernel::Rectangle::calculate_area()
{

    float side_1 = _edges[0].get_length();
    float side_2 = _edges[1].get_length();

    _area = side_1 * side_2;

}

float Geokernel::Rectangle::get_area() const
{

    return _area;

}

void Geokernel::Rectangle::print_stream_out()
{

    std::cout << "Rectangle:" << std::endl;
    std::cout << "1. Edge: " << std::endl;
    _edges[0].print_stream_out();
    std::cout << "2. Edge: " << std::endl;
    _edges[1].print_stream_out();
    std::cout << "3. Edge: " << std::endl;
    _edges[2].print_stream_out();
    std::cout << "4. Edge: " << std::endl;
    _edges[3].print_stream_out();

}

float Geokernel::Rectangle::get_width() const
{

    return _edges[0].get_length();

}

float Geokernel::Rectangle::get_height() const
{

    return _edges[1].get_length();

}
