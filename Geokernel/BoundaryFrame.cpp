//
// Created by oguzhan on 05.07.18.
//

#include "BoundaryFrame.h"

Geokernel::BoundaryFrame::BoundaryFrame(const Geokernel::Types::GeometryContainerRef geometryContainerRef)
{
    _geometryContainer = geometryContainerRef;

    for(const auto &it : _geometryContainer)
    {
        it->get_vector_vertex(_fullVertexSet);
    }

    _convexHull = Geokernel::ConvexHull(_fullVertexSet);

}
