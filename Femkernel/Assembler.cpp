#include "Assembler.h"

Femkernel::Assembler::Assembler(float _E, float _nu, float _rho, float _thickness)
        : E(_E), nu(_nu), rho(_rho), thickness(_thickness)
{}

void Femkernel::Assembler::start_assembly(Geokernel::Types::GeometryContainer triangleSet, 
                                          Femkernel::TriangularEFT& triangularEFT,
                                          SparseMatrix<float>& K_master,
                                          SparseMatrix<float>& M_master )
{

    int idx = 0;
    for ( auto &it : triangleSet)
    {
        Femkernel::LinearTriangle linearTriangle( it, E, nu, rho, thickness );
        Matrix<float, 6, 6> Ke = linearTriangle.get_element_stiffness();
        Matrix<float, 6, 6> Me = linearTriangle.get_element_mass();
        Femkernel::Types::ElementFreedoms eft = triangularEFT.get_element(it);

        merge_element_into_master_stiffness(Ke, eft, K_master);
        merge_element_into_master_mass(Me, eft, M_master);
        idx++;
    }
}


void Femkernel::Assembler::merge_element_into_master_stiffness(Matrix<float, 6, 6>& Ke, 
                                                               Femkernel::Types::ConstElementFreedomsRef eft, 
                                                               SparseMatrix<float>& K_master)
{
    for (int i=0; i < 6; i++)
    {
        size_t ii = eft[i]-1;
        for (int j = i; j < 6; j++)
        {
            size_t jj = eft[j]-1;
            K_master.coeffRef(ii,jj) +=  Ke(i,j);
            K_master.coeffRef(jj,ii) = K_master.coeff(ii,jj);
        }
    }    
}

// TODO put stiffness matrix and mass matrix in one loop. Make two function for static solver (without M) and one for modal analysis (with M)
void Femkernel::Assembler::merge_element_into_master_mass(Matrix<float, 6, 6>& Me,
                                                          Femkernel::Types::ConstElementFreedomsRef eft,
                                                          SparseMatrix<float>& M_master)
{
      for (int i=0; i < 6; i++)
    {
        size_t ii = eft[i]-1;
        for (int j = i; j < 6; j++)
        {
            size_t jj = eft[j]-1;
            M_master.coeffRef(ii,jj) +=  Me(i,j);
            M_master.coeffRef(jj,ii) = M_master.coeff(ii,jj);
        }
    }    
}

void Femkernel::Assembler::apply_boundary_conditions(std::vector<int> pdof, 
                                                     SparseMatrix<float>& K_master, 
                                                     SparseMatrix<float>& M_master, 
                                                     SparseVector<float>& F_master)
{
    long int systemSize = 0;

    if (K_master.rows() != M_master.rows() || 
        K_master.rows() != F_master.rows() || 
        K_master.rows() != K_master.cols())
        throw "Matrix and Vector dimensions of the system is not consistent";
    else
        systemSize = K_master.rows();

    for(int i=0; i < pdof.size(); i++)
    {
        int ii = pdof[i]-1;
        for(int jj=0; jj < systemSize; jj++)
        {
            K_master.coeffRef(ii,jj) = 0;
            K_master.coeffRef(jj,ii) = 0;

            M_master.coeffRef(ii,jj) = 0;
            M_master.coeffRef(jj,ii) = 0;
        }
        K_master.coeffRef(ii,ii) = 1;
        M_master.coeffRef(ii,ii) = 1;
        F_master.coeffRef(ii) = 0;
    }

}

// This function was just jused for debugging
void Femkernel::Assembler::apply_boundary_conditions_modal_analysis(std::vector<int> pdof,
                                                                            SparseMatrix<float>& K_master,
                                                                            SparseMatrix<float>& M_master,
                                                                            SparseVector<float>& F_master)
{
    long int systemSize = 0;

    if (K_master.rows() != M_master.rows() ||
        K_master.rows() != F_master.rows() ||
        K_master.rows() != K_master.cols())
        throw "Matrix and Vector dimensions of the system is not consistent";
    else
        systemSize = K_master.rows();

    for(int i=0; i < pdof.size(); i++)
    {
        int ii = pdof[i]-1;
        for(int jj=0; jj < systemSize; jj++)
        {
            K_master.coeffRef(ii,jj) = 0;
            K_master.coeffRef(jj,ii) = 0;

            M_master.coeffRef(ii,jj) = 0;
            M_master.coeffRef(jj,ii) = 0;
        }
        K_master.coeffRef(ii,ii) = 1e10;
        M_master.coeffRef(ii,ii) = 1;
        F_master.coeffRef(ii) = 0;
    }

}

// This function was just used for debugging
void Femkernel::Assembler::apply_boundary_conditions_by_deleting(   std::vector<int> pdof,
                                                                    SparseMatrix<float>& K_master,
                                                                    SparseMatrix<float>& M_master,
                                                                    SparseVector<float>& F_master,
                                                                    SparseMatrix<float>& K,
                                                                    SparseMatrix<float>& M,
                                                                    SparseVector<float>& F)
{
    long int systemSize = 0;

    if (K_master.rows() != M_master.rows() ||
        K_master.rows() != F_master.rows() ||
        K_master.rows() != K_master.cols())
        throw "Matrix and Vector dimensions of the system is not consistent";
    else
        systemSize = K_master.rows();

    int counter_i = 0;
    int counter_j = 0;
    for( int i = 0; i < systemSize - pdof.size(); i++)
    {
        if( i == pdof[i]-1 )
        {
            counter_i++;
        }
        for( int j = 0; j < systemSize - pdof.size(); j++)
        {
            if( j == pdof[j]-1 )
            {
                counter_j++;
            }

            M.coeffRef(i,j) = M_master.coeff(i+counter_i,j+counter_j);
            K.coeffRef(i,j) = K_master.coeff(i+counter_i,j+counter_j);
        }
    }
    /*
    for(int i=0; i < pdof.size(); i++)
    {
        int ii = pdof[i]-1;
        for(int jj=0; jj < systemSize; jj++)
        {
            K_master.coeffRef(ii,jj) = 0;
            K_master.coeffRef(jj,ii) = 0;

            M_master.coeffRef(ii,jj) = 0;
            M_master.coeffRef(jj,ii) = 0;
        }
        K_master.coeffRef(ii,ii) = 1e10;
        M_master.coeffRef(ii,ii) = 1;
        F_master.coeffRef(ii) = 0;
    }*/

}

