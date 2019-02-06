//
// Created by oguzhan on 30.06.18.
//

#ifndef FEMPACKAGE_ABSGEOMETRYELEMENT_H
#define FEMPACKAGE_ABSGEOMETRYELEMENT_H

#include <vector>
#include <array>
#include <memory>

namespace Geokernel
{

    class AbsGeometryElement
    {

    };

    namespace Types
    {

        typedef const std::vector<std::shared_ptr<AbsGeometryElement>> ConstGeoElementContainer;
        typedef std::vector<std::shared_ptr<AbsGeometryElement>> GeoElementContainer;


    }
}

#endif //FEMPACKAGE_ABSGEOMETRYELEMENT_H
