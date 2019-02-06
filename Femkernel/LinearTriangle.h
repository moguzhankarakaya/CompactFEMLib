#ifndef FEMPACKAGE_LINEARTRIANGLE_H
#define FEMPACKAGE_LINEARTRIANGLE_H

#include "../Geokernel/Triangle.h"
#include "../Geokernel/PrimaryTypes.h"
#include "../Geokernel/Vertex.h"
#include "../Geokernel/GeometryTypes.h"
#include "../External/Eigen/Eigen/Dense"

using namespace Eigen;

namespace Femkernel
{
    class LinearTriangle
    {
        private:
            Geokernel::Types::AbsGeometryPointer _triangle;
            Matrix<float, 3, 6> Bmatrix;
            Matrix<float, 3, 3> MaterialMatrix;
            Matrix<float, 6, 6> Ke;
            Matrix<float, 6, 6> Me;
            float E;
            float nu;
            float thickness;
            float rho;

        public:
            LinearTriangle( Geokernel::Types::AbsGeometryPointer triangle,
                            float _E,
                            float _nu,
                            float _rho,
                            float _thickness);

            void compute_mass_matrix();

            void compute_material_matrix();

            void compute_B_matrix();

            void compute_stiffness_matrix();

            Matrix<float, 6, 6>& get_element_stiffness();

            Matrix<float, 6, 6>& get_element_mass();

            Matrix<float, 3, 6>& get_B_matrix();

            Matrix<float, 3, 3>& get_material_matrix();

    };

}

#endif //FEMPACKAGE_LINEARTRIANGLE_H