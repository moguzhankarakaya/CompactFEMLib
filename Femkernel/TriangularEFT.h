//
// Created by oguzhan on 04.09.18.
//

#ifndef FEMPACKAGE_ELEMENTFREEDOMTABLE_H
#define FEMPACKAGE_ELEMENTFREEDOMTABLE_H


#include <map>
#include "../Geokernel/GeometryTypes.h"
#include "Types.h"

namespace Femkernel
{
    class TriangularEFT
    {
    public:

        TriangularEFT();

        void register_element(Geokernel::Types::AbsGeometryPointer key,
                              Types::ElementFreedoms *value);

        Types::ElementFreedomsRef get_element(Geokernel::Types::AbsGeometryPointer key);

    private:

        struct ElementFreedomPair
        {
            Geokernel::Types::AbsGeometryPointer _key;
            Types::ElementFreedoms *_value;
        };

        std::vector<ElementFreedomPair*> _triangularEFT;

    };

}


#endif //FEMPACKAGE_ELEMENTFREEDOMTABLE_H
