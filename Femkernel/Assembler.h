#ifndef FEMPACKAGE_ASSEMBLER
#define FEMPACKAGE_ASSEMBLER

#include "AbsMesher.h"
#include "../Geokernel/ConvexHull.h"
#include "../Geokernel/Triangle.h"
#include "LinearTriangle.h"
#include "../External/Eigen/Eigen/Sparse"
#include "../External/Eigen/Eigen/Dense"


using namespace Eigen;

namespace Femkernel
{

    class Assembler 
    {
    public:
        Assembler(float, float, float, float);

        void start_assembly(Geokernel::Types::GeometryContainer triangleSet, 
                            Femkernel::TriangularEFT& EFT_table, 
                            SparseMatrix<float>& K_master,
                            SparseMatrix<float>& M_master);

        void merge_element_into_master_stiffness(Matrix<float, 6, 6>& Ke,
                                                 Femkernel::Types::ConstElementFreedomsRef eft,
                                                 SparseMatrix<float>& K_master);

        void merge_element_into_master_mass(Matrix<float, 6, 6>& Me,
                                            Femkernel::Types::ConstElementFreedomsRef eft,
                                            SparseMatrix<float>& M_master);

        void apply_boundary_conditions(std::vector<int> pdof,
                                       SparseMatrix<float>& K_master,
                                       SparseMatrix<float>& M_master, 
                                       SparseVector<float>& F_master);

        void apply_boundary_conditions_modal_analysis(std::vector<int> pdof,
                                                      SparseMatrix<float>& K_master,
                                                      SparseMatrix<float>& M_master,
                                                      SparseVector<float>& F_master);

        void apply_boundary_conditions_by_deleting(   std::vector<int> pdof,
                                                        SparseMatrix<float>& K_master,
                                                        SparseMatrix<float>& M_master,
                                                        SparseVector<float>& F_master,
                                                        SparseMatrix<float>& K,
                                                        SparseMatrix<float>& M,
                                                        SparseVector<float>& F);

    private:
        float E;
        float nu;
        float rho;
        float thickness;

    };

}

#endif //FEMPACKAGE_ASSEMBLER
