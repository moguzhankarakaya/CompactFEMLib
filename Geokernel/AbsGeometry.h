//
// Created by oguzhan on 10.06.18.
//

#ifndef FEMPACKAGE_ABSGEOMETRY_H
#define FEMPACKAGE_ABSGEOMETRY_H

#include <vector>
#include <array>
#include <memory>

#include "Vertex.h"
#include "Edge.h"
#include "PrimaryTypes.h"


namespace Geokernel
{

    class AbsGeometry
    {
    private:


    public:
        virtual bool isInside(const Vertex& vertex) = 0;
        virtual void isInside(Types::VertexContainerRef vertexContainer, std::vector<char>& checkList) = 0;
        virtual void get_vector_vertex(Types::VertexContainerRef container) = 0;
        virtual void print_stream_out() = 0;
        virtual float get_area() const = 0;
    };
}

#endif //FEMPACKAGE_ABSGEOMETRY_H
