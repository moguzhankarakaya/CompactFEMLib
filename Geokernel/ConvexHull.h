//
// Created by oguzhan on 30.06.18.
//

#ifndef FEMPACKAGE_CONVEXHULL_H
#define FEMPACKAGE_CONVEXHULL_H


#include "PrimaryTypes.h"
#include "Vertex.h"
#include "Edge.h"

namespace Geokernel
{
    class ConvexHull {

    public:

        ConvexHull() = default;

        explicit ConvexHull(Types::VertexContainerRef vertexContainer);

        explicit ConvexHull(Types::VertexQuadRef vertexQuad);

        explicit ConvexHull(Types::CoordinateQuadRef coordinateQuad);

        ConvexHull& operator=(const ConvexHull& rhs);

        void calculate_convex_hull();

        Types::VertexContainer get_convex_hull() const;

        void stream_convex_hull();

    private:

        Types::ConstVertexContainerRef get_vertices() const;

        // Swap the bottommost element with the first element
        void bring_bottommost_head();

        // To find orientation of ordered triplet (p, q, r).
        // The function returns following values
        // 0 --> p, q and r are co-linear
        // 1 --> Clockwise
        // 2 --> Counterclockwise
        static int orientation(Vertex p, Vertex q, Vertex r);

    private:

        Types::VertexContainer _vertexContainer;

        Types::VertexContainer _convexHull;

    };
}

#endif //FEMPACKAGE_CONVEXHULL_H
