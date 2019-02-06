//
// Created by oguzhan on 15.06.18.
//

#ifndef FEMPACKAGE_TYPES_H
#define FEMPACKAGE_TYPES_H

#include <vector>
#include <array>
#include <memory>
#include "Vertex.h"
#include "Edge.h"

namespace Geokernel
{
    namespace Types {

        typedef const std::vector<Geokernel::Edge> ConstEdgeContainer;
        typedef const std::vector<Geokernel::Edge>& ConstEdgeContainerRef;
        typedef std::vector<Geokernel::Edge> EdgeContainer;
        typedef std::vector<Geokernel::Edge> &EdgeContainerRef;
        typedef std::array<Geokernel::Edge, 2> EdgePair;
        typedef std::array<Geokernel::Edge, 4> EdgeQuad;
        typedef std::array<Geokernel::Edge, 3> EdgeTrio;
        typedef std::array<Geokernel::Edge, 2> &EdgePairRef;
        typedef std::array<Geokernel::Edge, 4> &EdgeQuadRef;
        typedef std::array<Geokernel::Edge, 3> &EdgeTrioRef;

        typedef const std::vector<Geokernel::Vertex::Coordinate> ConstCoordinateContainer;
        typedef const std::vector<Geokernel::Vertex::Coordinate>& ConstCoordinateContainerRef;
        typedef std::vector<Geokernel::Vertex::Coordinate> CoordinateContainer;
        typedef std::vector<Geokernel::Vertex::Coordinate> &CoordinateContainerRef;
        typedef std::array<Geokernel::Vertex::Coordinate, 2> CoordinatePair;
        typedef std::array<Geokernel::Vertex::Coordinate, 4> CoordinateQuad;
        typedef std::array<Geokernel::Vertex::Coordinate, 3> CoordinateTrio;
        typedef std::array<Geokernel::Vertex::Coordinate, 2> &CoordinatePairRef;
        typedef std::array<Geokernel::Vertex::Coordinate, 4> &CoordinateQuadRef;
        typedef std::array<Geokernel::Vertex::Coordinate, 3> &CoordinateTrioRef;

        typedef const std::vector<Geokernel::Vertex> ConstVertexContainer;
        typedef const std::vector<Geokernel::Vertex>& ConstVertexContainerRef;
        typedef std::vector<Geokernel::Vertex> VertexContainer;
        typedef std::vector<Geokernel::Vertex> &VertexContainerRef;
        typedef std::vector<Geokernel::Vertex>&& VertexContainerMove;
        typedef std::array<Geokernel::Vertex, 2> VertexPair;
        typedef std::array<Geokernel::Vertex, 4> VertexQuad;
        typedef std::array<Geokernel::Vertex, 3> VertexTrio;
        typedef std::array<Geokernel::Vertex, 2> &VertexPairRef;
        typedef std::array<Geokernel::Vertex, 4> &VertexQuadRef;
        typedef std::array<Geokernel::Vertex, 3> &VertexTrioRef;

    }
}
#endif //FEMPACKAGE_TYPES_H
