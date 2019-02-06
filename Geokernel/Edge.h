//
// Created by oguzhan on 10.06.18.
//

#ifndef FEMPACKAGE_EDGE_H
#define FEMPACKAGE_EDGE_H

#include "Vertex.h"
#include "AbsGeometryElement.h"

namespace Geokernel {

    class Edge : public AbsGeometryElement
    {

    public:

        Edge();

        Edge(const Vertex& a, const Vertex& b);

        explicit Edge(const VertexPairRef vertexPair);

        Edge(const Edge& edge);

        ~Edge();

        VertexPair get_vertices( ) const;

        void set_vertices(const VertexPairRef _vertices);

        void set_vertices(const Vertex& a, const Vertex& b);

        void set_vertices(const Vertex::Coordinate& v1, const Vertex::Coordinate& v2);

        VertexContainer get_mid_vertices( ) const;

        size_t get_num_of_mid_vertices( ) const;

        float get_slope( ) const;

        void calculate_slope( );

        float get_length( ) const;

        void calculate_length( );

        bool is_on_edge(const Vertex& vertex);

        void divide_edge(int numOfDivisorPoints);

        void divide_edge(const Vertex& vertex);

        void print_stream_out();

    private:

        VertexPair _vertices;

        VertexContainer _midVertices;

        float _slope;

        float _length;

        bool _isSlopeSet;

    };
}

#endif //FEMPACKAGE_EDGE_H
