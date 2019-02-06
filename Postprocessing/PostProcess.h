//
// Created by oguzhan on 05.11.18.
//

#ifndef FEMPACKAGE_POSTPROCESS_H
#define FEMPACKAGE_POSTPROCESS_H
#include <iostream>

#include "../Femkernel/TriangularEFT.h"
#include "../External/Eigen/Eigen/Sparse"
#include "../External/Eigen/Eigen/Dense"
#include "../Femkernel/LinearTriangle.h"
#include "Types.h"

using namespace Eigen;

typedef Matrix<float, 6, 1> Vector6f;
typedef Matrix<float, 6, 1>& Vector6fRef;
typedef Matrix<float, 3, 1> Vector3f;
typedef Matrix<float, 3, 1>& Vector3fRef;
typedef Matrix<float, 3, 6> Matrix6f;
typedef Matrix<float, 3, 6>& Matrix6fRef;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 3, 3>& Matrix3fRef;

namespace Postprocessing
{
    class PostProcessor
    {
    public:

        PostProcessor(Geokernel::Types::GeometryContainerRef elements,
                      Femkernel::TriangularEFT& eft,
                      SparseVector<float>& displacement,
                      float _E, float _nu, float _rho, float _thickness);

        void get_element_displacements(Vector6fRef element_displacements,
                                       Femkernel::Types::ElementFreedomsRef elementFreedoms);

        void post_process();

        Types::PostProcessedDataRef get_post_processed_result(Geokernel::Types::AbsGeometryPointer key);

    private:

        // Private member functions used during calculations

        // Private members of class PostProcess

        Geokernel::Types::GeometryContainer _elements;
        Femkernel::TriangularEFT _eft;
        SparseVector<float> _displacements;
        float _E;
        float _nu;
        float _rho;
        float _thickness;

        struct PostProcessedDataPair
        {
            Geokernel::Types::AbsGeometryPointer _key;
            Types::PostProcessedData *_value;
        };

        Vector3f _strains;
        Vector3f _stresses;

        std::vector<PostProcessedDataPair*> _postProcessedDataTable;
    };
}
#endif //FEMPACKAGE_POSTPROCESS_H
