//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_ABSMESHER_H
#define FEMPACKAGE_ABSMESHER_H

#include "../Geokernel/GeometryTypes.h"
#include "../Geokernel/PrimaryTypes.h"
#include "TriangularEFT.h"

namespace Femkernel
{
    class AbsMesher
    {

    public:

        virtual void start_mesh(Geokernel::Types::ConstGeometryContainer* geometryContainer,
                                Geokernel::Types::GeometryContainer* triangleSet,
                                Femkernel::TriangularEFT* triangularEFT,
                                size_t numOfElemX, size_t numOfElemY, size_t numOfElemZ,
                                size_t *numOfGlobalNodes) = 0;

    private:

        Geokernel::Types::ConstGeometryContainer *_geometryContainer;
        Geokernel::Types::GeometryContainer *_triangleSet;

    };
}

#endif //FEMPACKAGE_ABSMESHER_H
