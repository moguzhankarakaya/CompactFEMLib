//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_BOUNDARYFRAME_H
#define FEMPACKAGE_BOUNDARYFRAME_H

#include "ConvexHull.h"
#include "GeometryTypes.h"

namespace Geokernel {

    class BoundaryFrame {
    private:

        explicit BoundaryFrame(const Types::GeometryContainerRef geometryContainerRef);

    public:

        Types::GeometryContainer _geometryContainer;

        Types::VertexContainer _fullVertexSet;

        ConvexHull _convexHull;

        Types::VertexContainer _boundaryFrame;
    };

}

#endif //FEMPACKAGE_BOUNDARYFRAME_H
