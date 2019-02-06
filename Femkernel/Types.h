//
// Created by oguzhan on 04.09.18.
//

#include <map>
#include "../Geokernel/AbsGeometry.h"
#include "../Geokernel/GeometryTypes.h"

#ifndef FEMPACKAGE_TYPES_H
#define FEMPACKAGE_TYPES_H

#endif //FEMPACKAGE_TYPES_H


namespace Femkernel
{
    namespace Types
    {

        typedef const std::array<size_t , 6> ConstElementFreedoms;
        typedef std::array<size_t, 6> ElementFreedoms;
        typedef const std::array<size_t, 6>& ConstElementFreedomsRef;
        typedef std::array<size_t, 6>& ElementFreedomsRef;
    }
}
