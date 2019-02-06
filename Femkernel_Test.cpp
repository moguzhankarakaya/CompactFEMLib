//
// Created by oguzhan on 05.07.18.
//
#include <iostream>
#include <ctime>
#include "Geokernel/ConvexHull.h"
#include "Utilities/Bithacks.h"
#include "Geokernel/GeometryTypes.h"
#include "Femkernel/Assembler.h"
#include "Geokernel/Rectangle.h"
#include "Geokernel/Vertex.h"
#include "Femkernel/Mesher2D.h"
#include "Femkernel/MeshFactory2D.h"
#include "Femkernel/TriangularEFT.h"
#include "Mathkernel/harmonicSolver.h"
#include "External/Eigen/Eigen/Sparse"
#include "External/Eigen/Eigen/SparseCholesky"

using namespace Eigen;

int main()
{
    // Parse geo from json
    Geokernel::Vertex* lowleft = new Geokernel::Vertex(0.0f, 0.0f);
    Geokernel::Vertex* upright = new Geokernel::Vertex(3.0f, 2.0f);

    Geokernel::Types::GeometryContainer geometry;
    Geokernel::Rectangle* rectangle  =  new Geokernel::Rectangle(*lowleft, *upright);
    geometry.push_back( std::shared_ptr<Geokernel::AbsGeometry>(rectangle)); 

    // send geometry to mesher
    Geokernel::Types::GeometryContainer meshedGeo;
    Femkernel::TriangularEFT EFT;

    // set mesh size here
    Femkernel::MeshFactory2D* meshFactory2D = new Femkernel::MeshFactory2D(geometry, meshedGeo, EFT, 5, 5);
    Femkernel::Mesher2D* mesher2D = new Femkernel::Mesher2D();

    meshFactory2D->register_mesher(mesher2D);
    size_t numOfDoF = 2* meshFactory2D->generate_mesh();
    std::cout << "\nnumOfDoF: " << numOfDoF << std::endl;

    // end of mesher -> send as a json 
    SparseMatrix<float> K(numOfDoF,numOfDoF);
    SparseMatrix<float> M(numOfDoF,numOfDoF);

    SparseVector<float> F(numOfDoF);
    std::vector<int> pdof;


    std::cout << "\nStart of Assembly: " << std::endl;
    Femkernel::Assembler* assembler = new Femkernel::Assembler(2e11, 0.3, 7.87, 0.1);
    assembler->start_assembly(meshedGeo, EFT, K, M);
    std::cout << "\nEnd of Assembly: " << std::endl;

    pdof.push_back(1); pdof.push_back(2); pdof.push_back(12);
    pdof.push_back(61); pdof.push_back(62);
    F.coeffRef(71) = -1000;

    std::cout << "\nStart of BC: " << std::endl;
    assembler->apply_boundary_conditions(pdof, K, M, F);
    std::cout << "\nEnd of BC: " << std::endl;

    SimplicialLLT<SparseMatrix<float>> solver;
    SparseMatrix<float> I(numOfDoF,numOfDoF);
    I.setIdentity();
    solver.compute(K);

    if(solver.info()!=Success)
    {
        std::cout << "Matrix is not invertible!";
    }

    SparseVector<float> disp = solver.solve(I)*F;

    for ( int j = 0; j < numOfDoF; j++ )
        std::cout << disp.coeff(j) << std::endl; ;
    std::cout << std::endl;

    long int begin, end;
    double elapsed_secs;
    // Harmonic Solver
    std::cout << "\nStart of Dynamic Solver: " << std::endl;
    begin = clock();


    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "\nEnd of Dynamic Solver: (elapsed time: " << elapsed_secs << "s )"  << std::endl;
    std::cout << std::endl;

    std::cout << "Displacement (Harmonic Solver): " << std::endl;

    return 0;
}