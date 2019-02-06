#ifndef ModalAnalysis_H
#define ModalAnalysis_H

#include<iostream>
#include "math.h"
#include <complex>

// External Libraries
#include "../External/Eigen/Eigen/Eigenvalues"
#include "../External/Eigen/Eigen/Sparse"
#include "../External/Spectra/include/SymGEigsSolver.h"
#include "../External/Spectra/include/MatOp/DenseSymMatProd.h"
#include "../External/Spectra/include/MatOp/SparseCholesky.h"

// Link: How to solve eigenvalue problems when using Sparse Matrics
//https://scicomp.stackexchange.com/questions/26786/eigen-max-and-minimum-eigenvalues-of-a-sparse-matrix

using namespace Eigen;

typedef Eigen::SparseMatrix<float> SparseMat;
typedef Eigen::SparseVector<float> SparseVec;
typedef Eigen::SimplicialLDLT<SparseMat> SparseChol;
//typedef Eigen::ArpackGeneralizedSelfAdjointEigenSolver <SparseMat> Arpack;


namespace Mathkernel
{

class ModalAnalysis
{
    private:
        MatrixXf eigenvectors;
        VectorXf eigenvalues;

        VectorXf K_red;
        // VectorXd M_red; is just one and therefore not needed
        VectorXf F_red;

        MatrixXf responses;

        Eigen::SparseMatrix<std::complex<float>> responsesD;

        VectorXf frequencyArray;

        float alpha;
        float beta;
        
        int numOfEigenvalues;
        int numOfFrequencies;
     
        int dim;

    public:
        ModalAnalysis( int _dim ) : dim(_dim)
        {
        }

        void SolveEigenvalueProblem( SparseMat& K, SparseMat& M, int numOfeig  )
        {
            numOfEigenvalues = numOfeig;

            // Solver already provides eigenvectors normalized with respect to mass matrix
            //Arpack es( K,M, ComputeEigenvectors|Ax_lBx );
            Spectra::SparseSymMatProd<float> A(K);
            Spectra::SparseCholesky<float>  B(M);

            Spectra::SymGEigsSolver<float, Spectra::SMALLEST_MAGN, Spectra::SparseSymMatProd<float>, Spectra::SparseCholesky<float>, Spectra::GEIGS_CHOLESKY>
            geigs(&A, &B, numOfEigenvalues, dim-1); // For some reason you can only get dim-2 eigenvalues

            // Initialize and compute
            geigs.init();
            int nconv = geigs.compute();
            // Retrieve results
            eigenvalues = geigs.eigenvalues();
            eigenvectors = geigs.eigenvectors();

            /*
            for( int i = 0; i < numpDof; i++) {
                eigenvalues.coeffRef(numpDof) = 0.0;
            }

            for( int i = 0; i < numpDof; i++)
            {
                float a = sqrt( eigenvalues.coeff(i) ) / ( 2 * M_PI);
                std::cout << a << std::endl;
            }*/

        }

        void computeRayleighCoeffs( double D1, double D2, int numPDOf )
        {
            double omega1 = sqrt( eigenvalues(numOfEigenvalues-1-numPDOf) );
            double a = eigenvalues(numOfEigenvalues-2-numPDOf);
            std::cout << a;
            double omega2 = sqrt( eigenvalues(numOfEigenvalues-2-numPDOf) );

            double tmpCoeff = 2 * omega1 * omega2 / ( pow(omega2,2) - pow(omega1,2) );

            alpha = tmpCoeff * (omega2 * D1 - omega1 * D2 );
            beta = tmpCoeff * ( -1/omega2 * D1 + 1/omega1 * D2 );
        }

        void computeModalMatrices( SparseMat& K, SparseMat& M, SparseVec& F )
        {
            // With this you can check if K_red and M_red are correct
            // K_red =  eigenvectors.transpose() * (K * eigenvectors); K_red is just eigenvalues
            // M_red = eigenvectors.transpose() * (M * eigenvectors);  M_red is identity!
            K_red = eigenvalues;
            F_red = eigenvectors.transpose() * F;
            /*
            std::cout << "K_reduced: \n" << K_red << std::endl; 
            std::cout << "M_reduced: \n" << M_red << std::endl; 
            std::cout << "F_reduced: \n" << F_red << std::endl; */
        }


        void computeDisplacements( double start, double _end, int numOfFrequencies, MatrixXf& disp )
        {
            frequencyArray = VectorXf::LinSpaced(numOfFrequencies, start, _end);
            
            responses.resize(numOfEigenvalues,numOfFrequencies);
            disp = MatrixXf::Zero(dim,numOfFrequencies);

            for( int j = 0; j < numOfFrequencies; j++)
            {
                for(int i = 0; i < numOfEigenvalues; i++)
                {
                    // Check units of frequency
                    responses(i,j) = F_red.coeff(i)/ ( eigenvalues[i] - pow(frequencyArray[j]*2*M_PI,2) );
                    disp.col(j) +=   responses(i,j) * eigenvectors.col(i);

                }
            }
        }

        //TODO This function should be checked again (not validated yet!)
        void computeDisplacementsWithDamping( int start, int _end, int numOfFrequencies, MatrixXf& disp )
        {
            frequencyArray = VectorXf::LinSpaced(numOfFrequencies, start, _end);

            responsesD.resize(numOfEigenvalues,numOfFrequencies);
            disp = MatrixXf::Zero(dim,numOfFrequencies);

            //using namespace std::complex_literals;
            //std::complex<double> z = 1i;

            double eta;
            std::complex<float> A;
            std::complex<float> B;

            for( int j = 0; j < numOfFrequencies; j++)
            {
                for(int i = 0; i < numOfEigenvalues; i++)
                {
                    eta = 1 / ( 2 * sqrt(eigenvalues[i]) ) * alpha + sqrt( eigenvalues[i] ) / 2 * beta;
                    std::cout << alpha << beta << std::endl;
                    std::complex<float>  complexNumber( ( eigenvalues[i] - pow( frequencyArray[j]*2*M_PI , 2)), ( 2*eta* sqrt(eigenvalues[i]) * frequencyArray[j] *2 *M_PI) );
                    A = F_red.coeff(i);

                    B = (A/ complexNumber);
                    if( isnan( abs(B) ) )
                    {
                        B = 0.0;
                    }

                    disp.col(j) +=  abs(B) * eigenvectors.col(i);
                }
            }
        }


        VectorXf getEigenvalue()
        {
            return eigenvalues;
        }

        VectorXf getEigenfrequenciesRad()
        {
            return eigenvalues.cwiseSqrt();
        }

        float getEigenfrequenciesHzAt(int i)
        {
            return sqrt(eigenvalues[i])/(2.0*M_PI);
        }

        MatrixXf getEigenvectors()
        {
            return eigenvectors;
        }


        float getFrequencieAt(int i)
        {
            return frequencyArray[i];
        }

        float getAlpha()
        {
            return alpha;
        }

        float getBeta()
        {
            return beta;
        }
};
} // namespace Mathkernel

#endif
