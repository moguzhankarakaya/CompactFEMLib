//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_MESHER2D_H
#define FEMPACKAGE_MESHER2D_H

#include "AbsMesher.h"
#include "../Geokernel/ConvexHull.h"

namespace Femkernel
{

    class Mesher2D : public AbsMesher
    {
    public:

        Mesher2D();

        void start_mesh(Geokernel::Types::ConstGeometryContainer *geometryContainer,
                        Geokernel::Types::GeometryContainer *triangleSet,
                        Femkernel::TriangularEFT* triangularEFT,
                        size_t numOfElemX, size_t numOfElemY, size_t numOfElemZ, size_t* numOfGlobalNodes) override;

        Femkernel::TriangularEFT getTriangularEFT() { return  *_triangularEFT; }

        void extract_far_most_points();

        void scatter_equidistant_grid_points();

        void grid_points_inside_geometry();

        void triangulate_grid_points();

        void headsUpTriangulation(size_t target, size_t right, size_t upCorner);

        void headsDownTriangulation(size_t target, size_t right, size_t down);

    private:
        Geokernel::Types::GeometryContainer *_triangleSet;

        Geokernel::Types::ConstGeometryContainer *_geometryContainer;

        Femkernel::TriangularEFT *_triangularEFT;

        size_t _numOfElemX, _numOfElemY;

        size_t* _numOfGlobalNodes;

        Geokernel::Vertex _bottomMostVertex;

        Geokernel::Vertex _topMostVertex;

        Geokernel::Types::VertexContainer _fullVertexSet;

        Geokernel::Types::VertexContainer _vertexHull;

        Geokernel::Types::VertexContainer _scatteredVertices;

        std::vector<char> _insideDomainPoints;

        std::vector<size_t> _nodeNumbers;

    };

}

#endif //FEMPACKAGE_MESHER2D_H
