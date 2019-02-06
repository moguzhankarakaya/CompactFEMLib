//
// Created by oguzhan on 05.07.18.
//

//Standard Includes
#include <iostream>
#include <cmath>

//Project Includes
#include "Mesher2D.h"
#include "../Utilities/Bithacks.h"
#include "../Utilities/Constants.h"
#include "../Geokernel/Triangle.h"

Femkernel::Mesher2D::Mesher2D() = default;

void Femkernel::Mesher2D::start_mesh(Geokernel::Types::ConstGeometryContainer *geometryContainer,
                                     Geokernel::Types::GeometryContainer *triangleSet,
                                     Femkernel::TriangularEFT* triangularEFT,
                                     size_t numOfElemX, size_t numOfElemY, size_t numOfElemZ,
                                     size_t* numOfGlobalNodes)
{
    _geometryContainer = geometryContainer;
    _triangleSet       = triangleSet;
    _triangularEFT     = triangularEFT;
    _numOfElemX = numOfElemX;
    _numOfElemY = numOfElemY;
    _numOfGlobalNodes = numOfGlobalNodes;

    if(_numOfElemX <= 0 || _numOfElemY <= 0) throw std::string("Improper mesh number");

    for(const auto &it : *_geometryContainer)
    {
        it->get_vector_vertex(_fullVertexSet);
    }

    Geokernel::ConvexHull convexHull(_fullVertexSet);
    convexHull.calculate_convex_hull();
    _vertexHull = convexHull.get_convex_hull();

    extract_far_most_points();

    scatter_equidistant_grid_points();

    grid_points_inside_geometry();

    triangulate_grid_points();

}

void Femkernel::Mesher2D::extract_far_most_points()
{
    _bottomMostVertex = _vertexHull[0];
    _topMostVertex = _vertexHull[0];

    for(const auto &it : _vertexHull)
    {
        if(_topMostVertex < it)
        {
            _topMostVertex = it;
        }
    }
}

void Femkernel::Mesher2D::scatter_equidistant_grid_points()
{
    float startX = _bottomMostVertex.get_coordinates()._x;

    float startY = _bottomMostVertex.get_coordinates()._y;

    float endX   = _topMostVertex.get_coordinates()._x;

    float endY   = _topMostVertex.get_coordinates()._y;

    float deltaX = std::abs(endX - startX) / _numOfElemX;

    float deltaY = std::abs(endY - startY) / _numOfElemY;

    if( deltaX < GlobalConstants::MIN_ALLOWABLE_MESH_SIZE ||
        deltaY < GlobalConstants::MIN_ALLOWABLE_MESH_SIZE)
    {
        throw std::string("Mesh size is smaller than target precision! Please decrease mesh size increase dimensions.");
    }

    PrimaryUtilities::Tolerance<float> checkConditionX(GlobalConstants::MESHER_VERTEX_PRECISION);
    PrimaryUtilities::Tolerance<float> checkConditionY(GlobalConstants::MESHER_VERTEX_PRECISION);
    checkConditionX.set_boundary(endX);
    checkConditionY.set_boundary(endY);

    for(float y = startY; y < endY || checkConditionY.check_value(y); y+= deltaY)
    {
        for(float x = startX; x < endX || checkConditionX.check_value(x); x+= deltaX)
        {
            if(y > endY) y = endY;
            if(x > endX) x = endX;
            _scatteredVertices.emplace_back(x, y);
        }
    }
}

void Femkernel::Mesher2D::grid_points_inside_geometry()
{
    std::vector<char> tempList;

    for(int i = 0; i < _scatteredVertices.size(); i++)
    {
        _insideDomainPoints.emplace_back(false);
    }

    for(const auto &it : *_geometryContainer)
    {
        it->isInside(_scatteredVertices, tempList);
        try
        {
            PrimaryUtilities::elementWiseOr(_insideDomainPoints, tempList);
        }
        catch(std::string message)
        {
            std::cout << message << std::endl;

        }
        std::vector<char>().swap(tempList);
    }

    size_t counter = 1;

    for(const auto &it : _insideDomainPoints)
    {

        if(it)
        {
            _nodeNumbers.push_back(counter);
            counter++;
        }
        else
        {
            _nodeNumbers.push_back(0);
        }
    }

    *_numOfGlobalNodes = counter - 1;
}

void Femkernel::Mesher2D::triangulate_grid_points()
{
    PrimaryUtilities::Indexer indexer(_numOfElemX + 1, _numOfElemY + 1);
    size_t target, upCorner, right, down;

    for(size_t j = 0; j < _numOfElemY + 1; j++)
    {
        for (size_t i = 0; i < _numOfElemX; i++)
        {

            target = indexer.get_index(i, j);
            right  = indexer.get_index(i + 1, j);

            if( j > 0)
            {
                down = indexer.get_index(i, j - 1);
                headsDownTriangulation(target, right, down);
            }

            if( j < _numOfElemY)
            {
                upCorner = indexer.get_index(i + 1, j + 1);
                headsUpTriangulation(target, right, upCorner);
            }
        }
    }
}

void Femkernel::Mesher2D::headsUpTriangulation(size_t target, size_t right, size_t upCorner)
{
    if(_insideDomainPoints[target] && _insideDomainPoints[right] && _insideDomainPoints[upCorner])
    {
        Geokernel::Triangle* tempTriangle = new Geokernel::Triangle(_scatteredVertices[target],
                                                                    _scatteredVertices[right],
                                                                    _scatteredVertices[upCorner]);
        for(const auto &it : *_geometryContainer)
        {
            if (it->isInside(tempTriangle->get_barycentric_point()))
            {
                (*_triangleSet).emplace_back(tempTriangle);
                auto elementFreedoms = new  Femkernel::Types::ElementFreedoms{2*_nodeNumbers[target] - 1,
                                                                              2*_nodeNumbers[target],
                                                                              2*_nodeNumbers[right] - 1,
                                                                              2*_nodeNumbers[right],
                                                                              2*_nodeNumbers[upCorner] - 1,
                                                                              2*_nodeNumbers[upCorner]};

                (*_triangularEFT).register_element(_triangleSet->back(), elementFreedoms);

                break;
            }
        }

    }
}

void Femkernel::Mesher2D::headsDownTriangulation(size_t target, size_t right, size_t down)
{
    if(_insideDomainPoints[target] && _insideDomainPoints[right] && _insideDomainPoints[down])
    {

        Geokernel::Triangle* tempTriangle = new Geokernel::Triangle(_scatteredVertices[target],
                                                                    _scatteredVertices[down],
                                                                    _scatteredVertices[right]);

        for(const auto &it : *_geometryContainer)
        {
            if (it->isInside(tempTriangle->get_barycentric_point()))
            {
                (*_triangleSet).emplace_back(tempTriangle);
                auto elementFreedoms = new  Femkernel::Types::ElementFreedoms{2*_nodeNumbers[target] - 1,
                                                                              2*_nodeNumbers[target],
                                                                              2*_nodeNumbers[down] - 1,
                                                                              2*_nodeNumbers[down],
                                                                              2*_nodeNumbers[right] - 1,
                                                                              2*_nodeNumbers[right]};

                (*_triangularEFT).register_element(_triangleSet->back(), elementFreedoms);

                break;
            }
        }

    }
}
