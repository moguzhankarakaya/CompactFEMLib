//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_GEOMETRYTYPES_H
#define FEMPACKAGE_GEOMETRYTYPES_H

#include "AbsGeometry.h"

namespace Geokernel
{
    namespace Types
    {

        typedef const std::vector<std::shared_ptr<AbsGeometry>>& ConstGeometryContainerRef;
        typedef const std::vector<std::shared_ptr<AbsGeometry>> ConstGeometryContainer;
        typedef std::vector<std::shared_ptr<AbsGeometry>>& GeometryContainerRef;
        typedef std::vector<std::shared_ptr<AbsGeometry>> GeometryContainer;
        typedef std::shared_ptr<AbsGeometry> AbsGeometryPointer;

    }
}


#endif //FEMPACKAGE_GEOMETRYTYPES_H
