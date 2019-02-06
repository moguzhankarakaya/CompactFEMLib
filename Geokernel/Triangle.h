//
// Created by oguzhan on 16.06.18.
//

#ifndef FEMPACKAGE_TRIANGLE_H
#define FEMPACKAGE_TRIANGLE_H

#include "PrimaryTypes.h"
#include "Vertex.h"
#include "Edge.h"
#include "AbsGeometry.h"

namespace Geokernel
{

    class Triangle : public AbsGeometry
    {
    public:

        Triangle();

        Triangle(const Types::VertexTrioRef vertexSet, const Types::EdgeTrioRef edgeSet);

        explicit Triangle(const Types::VertexTrioRef vertexSet);

        explicit Triangle(const Types::CoordinateTrioRef coordinateSet);

        explicit Triangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3);

        explicit Triangle(const Vertex::Coordinate& coordinate1,
                          const Vertex::Coordinate& coordinate2,
                          const Vertex::Coordinate& coordinate3);

        Triangle(const Triangle& rectangle);

        ~Triangle();

        Types::VertexTrio get_vertices() const;

        Types::EdgeTrio get_edges() const;

        void get_vector_vertex(Types::VertexContainerRef container) override;

        void set_vertices(const Types::VertexTrioRef vertexSet);

        void set_edges(const Types::EdgeTrioRef edgeSet);

        void calculate_area();

        float get_area() const override;

        float get_edge_length(int edgeNumber) const;

        bool isInside(const Vertex& vertex) override;

        void isInside(const Types::VertexContainerRef vertexContainer, std::vector<char>& checkList) override;

        Vertex get_barycentric_point() const;

        Vertex get_barycentric_point(float v1, float v2, float v3);

        void print_stream_out() override;


    private:

        Types::VertexTrio _vertices;

        Types::EdgeTrio _edges;

        float _area;

    };

}

#endif //FEMPACKAGE_TRIANGLE_H
