#ifndef HarmonicSolver_H
#define HarmonicSolver_H

#include<iostream>
//https://eigen.tuxfamily.org/dox/classEigen_1_1GeneralizedSelfAdjointEigenSolver.html#addc0409c9cb1a5ac9cbbd00efe68908e
#include "../External/Eigen/Eigen/Eigenvalues"
#include "pcgsolver.h"
#include "math.h"


using namespace Eigen;

namespace Mathkernel
{

class HarmonicSolver
{
    private:
        MatrixXd eigenvectors;
        VectorXd eigenvalues;

        MatrixXd K_red;
        MatrixXd M_red;
        VectorXd F_red;

        VectorXd disp;

        int dim;

    public:
        HarmonicSolver( int _dim ) : dim(_dim)
        {
        }

        void SolveEigenvalueProblem( Mathkernel::SparseMatrix<float>& _K, Mathkernel::SparseMatrix<float>& _M )
        {
            MatrixXd K = MatrixXd::Zero(dim,dim);
            MatrixXd M = MatrixXd::Zero(dim,dim);

            for( int i =  0; i < dim; i++ )
            {
                for( int j = 0; j < dim; j++ )
                {
                    K(i,j) = _K(i,j);
                    M(i,j) = _M(i,j);
                }
            }

            // Solver already return vectors normalized with respect to mass matrixS
            GeneralizedSelfAdjointEigenSolver<MatrixXd> es(K,M, ComputeEigenvectors|Ax_lBx );
            eigenvectors = es.eigenvectors();
            eigenvalues =  es.eigenvalues();
        }

        void computeModalMatrices( Mathkernel::SparseMatrix<float>& _K, Mathkernel::SparseMatrix<float>& _M, std::vector<float>& _F )
        {
            MatrixXd K = MatrixXd::Zero(dim,dim);
            MatrixXd M = MatrixXd::Zero(dim,dim);
            VectorXd F = VectorXd::Zero(dim);

            for( int i =  0; i < dim; i++ )
            {
                F(i) = _F[i];

                for( int j = 0; j < dim; j++ )
                {
                    K(i,j) = _K(i,j);
                    M(i,j) = _M(i,j);
                }
            }
        
            K_red =  eigenvectors.transpose() * (K * eigenvectors); // This can be changed as K_red is always eigenvalues!
            M_red = eigenvectors.transpose() * (M * eigenvectors);  // This can be changed as M_red is always identity!
            F_red = eigenvectors.transpose() * F;
            /*
            std::cout << "K_reduced: \n" << K_red << std::endl; 
            std::cout << "M_reduced: \n" << M_red << std::endl; 
            std::cout << "F_reduced: \n" << F_red << std::endl; */
        }

        void computeDisplacements()
        {
            disp = VectorXd::Zero(dim);
            for(int i = 0; i < dim; i++)
            {
                disp += ( F_red(i)/K_red(i,i) ) * eigenvectors.col(i);
            }
        }

        VectorXd getEigenvalue()
        {
            return eigenvalues;
        }

        VectorXd getEigenfrequenciesRad()
        {
            return eigenvalues.cwiseSqrt();
        }

        VectorXd getEigenfrequenciesHz()
        {
            return eigenvalues.cwiseSqrt()/(2.0*M_PI);
        }

        MatrixXd getEigenvectors()
        {
            return eigenvectors;
        }

        VectorXd getDisplacements()
        {
            return disp;
        }
};
} // namespace Mathkernel

#endif
