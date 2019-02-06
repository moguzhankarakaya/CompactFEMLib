//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_MESHFACTORY2D_H
#define FEMPACKAGE_MESHFACTORY2D_H

#include "AbsMeshFactory.h"
#include "../Geokernel/GeometryTypes.h"
#include "../Geokernel/ConvexHull.h"
#include "AbsMesher.h"
#include "TriangularEFT.h"

namespace Femkernel {

    class MeshFactory2D : public AbsMeshFactory{
    public:

        explicit MeshFactory2D(Geokernel::Types::ConstGeometryContainerRef geometryContainer,
                               Geokernel::Types::GeometryContainerRef triangleSet,
                               Femkernel::TriangularEFT& triangularEFT,
                               size_t numOfElemX, size_t numOfElemY);

        void register_mesher(AbsMesher* mesher) override;

        size_t generate_mesh();


    private:

        Geokernel::Types::ConstGeometryContainer* _geometryContainer;

        Geokernel::Types::GeometryContainer* _triangleSet;

        Femkernel::TriangularEFT* _triangularEFT;

        AbsMesher* _mesher;

        size_t _numOfElemX, _numOfElemY;

        size_t _numOfGlobalNodes;

    };

}

#endif //FEMPACKAGE_MESHFACTORY2D_H
