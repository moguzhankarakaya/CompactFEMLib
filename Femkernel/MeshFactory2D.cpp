//
// Created by oguzhan on 05.07.18.
//

#include "MeshFactory2D.h"

Femkernel::MeshFactory2D::MeshFactory2D(Geokernel::Types::ConstGeometryContainerRef geometryContainer,
                                        Geokernel::Types::GeometryContainerRef triangleSet,
                                        Femkernel::TriangularEFT& triangularEFT,
                                        size_t numOfElemX, size_t numOfElemY) :
        _numOfElemX(numOfElemX), _numOfElemY(numOfElemY), _triangularEFT(&triangularEFT),
        _geometryContainer(&geometryContainer), _triangleSet(&triangleSet)
{

}

void Femkernel::MeshFactory2D::register_mesher(Femkernel::AbsMesher *mesher)
{
    _mesher = mesher;
}

size_t Femkernel::MeshFactory2D::generate_mesh()
{
    _mesher->start_mesh(_geometryContainer, _triangleSet, _triangularEFT, _numOfElemX, _numOfElemY, 0, &_numOfGlobalNodes);

    return _numOfGlobalNodes;
}


