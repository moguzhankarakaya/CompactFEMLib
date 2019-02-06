//
// Created by oguzhan on 10.06.18.
//

#ifndef FEMPACKAGE_RECTANGLE_H
#define FEMPACKAGE_RECTANGLE_H

#include "PrimaryTypes.h"
#include "Vertex.h"
#include "Edge.h"
#include "AbsGeometry.h"


namespace Geokernel
{

    class Rectangle : public AbsGeometry
    {
    public:

        Rectangle();

        Rectangle(const Types::VertexQuadRef vertexSet, const Types::EdgeQuadRef edgeSet);

        explicit Rectangle(const Types::VertexQuadRef vertexSet);

        explicit Rectangle(const Types::CoordinateQuadRef coordinateSet);

        explicit Rectangle(const Types::VertexPairRef vertexPair);

        explicit Rectangle(const Types::CoordinatePairRef coordinatePair);

        explicit Rectangle(const Vertex& vertex1, const Vertex& vertex2);

        explicit Rectangle(const Vertex::Coordinate& coordinate1, const Vertex::Coordinate& coordinate2);

        Rectangle(const Rectangle& rectangle);

        ~Rectangle();

        Types::VertexQuad get_vertices() const;

        Types::EdgeQuad get_edges() const;

        void get_vector_vertex(Types::VertexContainerRef container) override;

        void set_vertices(const Types::VertexQuadRef vertexSet);

        void calculate_area();

        float get_area() const override;

        float get_width() const;

        float get_height() const;

        bool isInside(const Vertex& vertex) override;

        void isInside(const Types::VertexContainerRef vertexContainer, std::vector<char>& checkList) override;

        void print_stream_out() override;

    private:

        Types::VertexQuad _vertices;

        Types::EdgeQuad _edges;

        float _area;

    };

}

#endif //FEMPACKAGE_RECTANGLE_H
