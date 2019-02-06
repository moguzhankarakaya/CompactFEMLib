//
// Created by oguzhan on 10.06.18.
//

#ifndef FEMPACKAGE_VERTEX_H
#define FEMPACKAGE_VERTEX_H

#include <vector>
#include <array>
#include "ProblemType.h"
#include "AbsGeometryElement.h"

namespace Geokernel
{

    class Vertex : public AbsGeometryElement
    {

    public:

        struct Coordinate
        {
            float _x;
            float _y;
            float _z;

            Coordinate()
            {

                _x = 0; _y = 0; _z = 0;
            }

            Coordinate(float x, float y, float z): _x(x), _y(y), _z(z)
            {

            }

            Coordinate(const Coordinate& coordinate)
            {

                _x = coordinate._x;
                _y = coordinate._y;
                _z = coordinate._z;

            }

            bool operator<(const Coordinate& rhs) const
            {
                if (_y != rhs._y)
                    return _y < rhs._y;
                return _x < rhs._x;
            }

        };

    public:

        Vertex();

        Vertex(float x, float y);

        Vertex(float x, float y, float z);

        Vertex(const Vertex& vertex);

        explicit Vertex(const Coordinate& coordinate);

        Vertex& operator= (const Vertex& rhs);

        bool operator<(const Vertex& rhs) const;

        ~Vertex();

        const Coordinate& get_coordinates() const;

        void set_coordinates(const Coordinate& coordinate);

        void set_coordinates(float x, float y);

        void set_coordinates(float x, float y, float z);

        void print_stream_out();

    private:

        Coordinate _coordinate;

    };


    typedef const std::vector<Geokernel::Vertex> ConstVertexContainer;
    typedef const std::vector<Geokernel::Vertex>& ConstVertexContainerRef;
    typedef std::vector<Geokernel::Vertex> VertexContainer;
    typedef std::vector<Geokernel::Vertex>& VertexContainerRef;
    typedef std::array<Geokernel::Vertex, 2> VertexPair;
    typedef std::array<Geokernel::Vertex, 2>& VertexPairRef;

}

#endif //FEMPACKAGE_VERTEX_H
