//
// Created by oguzhan on 30.06.18.
//

#include <algorithm>
#include <iostream>

#include "ConvexHull.h"
#include "../Utilities/Bithacks.h"

Geokernel::ConvexHull::ConvexHull(const Geokernel::Types::VertexContainerRef vertexContainer)
{

    if (vertexContainer.size() < 3) throw "There should be at least three points two calculate convex hull.";

    _vertexContainer = vertexContainer;

    bring_bottommost_head();

}

Geokernel::ConvexHull::ConvexHull(const Geokernel::Types::VertexQuadRef vertexQuad)
{
    for(auto it : vertexQuad)
    {
        _vertexContainer.emplace_back(it);
    }

    bring_bottommost_head();

}

Geokernel::ConvexHull::ConvexHull(const Geokernel::Types::CoordinateQuadRef coordinateQuad)
{
    for(auto it : coordinateQuad)
    {
        _vertexContainer.emplace_back(Geokernel::Vertex(it));
    }

    bring_bottommost_head();

}

Geokernel::ConvexHull &Geokernel::ConvexHull::operator=(const Geokernel::ConvexHull& rhs)
{
    this->_vertexContainer = rhs.get_vertices();

    bring_bottommost_head();

    _convexHull.clear();

    return *this;
}

Geokernel::Types::ConstVertexContainerRef Geokernel::ConvexHull::get_vertices() const
{
    return _vertexContainer;
}

int Geokernel::ConvexHull::orientation(Geokernel::Vertex p, Geokernel::Vertex q, Geokernel::Vertex r)
{
    float area = (q.get_coordinates()._y - p.get_coordinates()._y) * \
                 (r.get_coordinates()._x - q.get_coordinates()._x) - \
                 (q.get_coordinates()._x - p.get_coordinates()._x) * \
                 (r.get_coordinates()._y - q.get_coordinates()._y);

    if (area == 0) return 0;  // co-linear

    return (area > 0)? 1: 2; // clockwise or counterclockwise
}

void Geokernel::ConvexHull::bring_bottommost_head()
{

    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    int leastY = 0;
    for (int i = 1; i < _vertexContainer.size(); i++)
        if (_vertexContainer[i] < _vertexContainer[leastY])
            leastY = i;

    PrimaryUtilities::swap(_vertexContainer[0], _vertexContainer[leastY]);
}

void Geokernel::ConvexHull::calculate_convex_hull()
{

    size_t p = 0, q = 0;
    auto cloudSize = _vertexContainer.size();
    do
    {

        _convexHull.push_back(_vertexContainer[p]);

        q = (p + 1) % cloudSize;

        for(size_t i = 0; i < cloudSize; i++)
        {
            if(orientation(_vertexContainer[p], _vertexContainer[i], _vertexContainer[q]) == 2)
                q = i;
        }

        p = q;

    } while(p != 0);
}

Geokernel::Types::VertexContainer Geokernel::ConvexHull::get_convex_hull() const
{
    return _convexHull;
}

void Geokernel::ConvexHull::stream_convex_hull()
{
    std::cout << std::endl <<"Convex Hull : " << std::endl;
    std::cout << std::string(20, '*') << std::endl;
    for(auto it : _convexHull) it.print_stream_out();
    std::cout << std::string(20, '*') << std::endl;
}


