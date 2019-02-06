#include "LinearTriangle.h"

Femkernel::LinearTriangle::LinearTriangle ( Geokernel::Types::AbsGeometryPointer triangle,
                                            float _E,
                                            float _nu,
                                            float _rho,
                                            float _thickness ) :
                                            E(_E),
                                            nu(_nu),
                                            thickness(_thickness),
                                            rho(_rho)
{
    _triangle = triangle;
    compute_material_matrix();
    compute_mass_matrix();
    compute_B_matrix();
    compute_stiffness_matrix();
}

void Femkernel::LinearTriangle::compute_material_matrix()
{
    float K = E / ( 1-nu*nu );

    MaterialMatrix(0,0) = K * 1;
    MaterialMatrix(0,1) = K * nu;
    MaterialMatrix(0,2) = 0.0;

    MaterialMatrix(1,0) = K * nu;
    MaterialMatrix(1,1) = K * 1;
    MaterialMatrix(1,2) = 0.0;

    MaterialMatrix(2,0) = 0.0;
    MaterialMatrix(2,1) = 0.0;
    MaterialMatrix(2,2) = K * (1-nu); //?? TODO shouldn't it be divided by 2? Check...
}

void Femkernel::LinearTriangle::compute_mass_matrix()
{
    // First row
    Me( 0,0 ) = 2;
    Me(0,1) = 0;
    Me( 0,2 ) = 1;
    Me(0,3) = 0;
    Me( 0,4 ) = 1;
    Me(0,5) = 0;
    // second row
    Me( 1,0 ) = 0;
    Me( 1,1 ) = 2;
    Me( 1,2 ) = 0;
    Me( 1,3 ) = 1;
    Me( 1,4 ) = 0;
    Me( 1,5 ) = 1;
    // Third row
    Me( 2,0 ) = 1;
    Me( 2,1 ) = 0;
    Me( 2,2 ) = 2;
    Me( 2,3 ) = 0;
    Me( 2,4 ) = 1;
    Me( 2,5 ) = 0;
    // Fourth row
    Me( 3,0 ) = 0;
    Me( 3,1 ) = 1;
    Me( 3,2 ) = 0;
    Me( 3,3 ) = 2;
    Me( 3,4 ) = 0;
    Me( 3,5 ) = 1;
    // Fifth row
    Me( 4,0 ) = 1;
    Me( 4,1 ) = 0;
    Me( 4,2 ) = 1;
    Me( 4,3 ) = 0;
    Me( 4,4 ) = 2;
    Me( 4,5 ) = 0;
    // Sixth row
    Me( 5,0 ) = 0;
    Me( 5,1 ) = 1;
    Me( 5,2 ) = 0;
    Me( 5,3 ) = 1;
    Me( 5,4 ) = 0;
    Me( 5,5 ) = 2;

    float area = _triangle->get_area();
    Me *= (rho * thickness * area / 12.0);
}

void Femkernel::LinearTriangle::compute_B_matrix()
{
    Geokernel::Types::VertexContainer vertices;
    _triangle->get_vector_vertex(vertices);

    float area = _triangle->get_area();
    float b1,b2,b3,c1,c2,c3;

    b1 = ( vertices[1].get_coordinates()._y - vertices[2].get_coordinates()._y );
    b2 = ( vertices[2].get_coordinates()._y - vertices[0].get_coordinates()._y );
    b3 = ( vertices[0].get_coordinates()._y - vertices[1].get_coordinates()._y );

    c1 = ( vertices[2].get_coordinates()._x - vertices[1].get_coordinates()._x );
    c2 = ( vertices[0].get_coordinates()._x - vertices[2].get_coordinates()._x );
    c3 = ( vertices[1].get_coordinates()._x - vertices[0].get_coordinates()._x );

    // First row
    Bmatrix(0,0) = 1.0f / ( 2.0f * area ) * b1;
    Bmatrix(0,1) = 0.0;
    Bmatrix(0,2) = 1.0f / ( 2.0f * area ) * b2;
    Bmatrix(0,3) = 0.0;
    Bmatrix(0,4) = 1.0f / ( 2.0f * area ) * b3;
    Bmatrix(0,5) = 0.0;

    // // Second row
    Bmatrix(1,0) = 0.0;
    Bmatrix( 1, 1 ) = 1.0f / ( 2.0f * area ) * c1;
    Bmatrix(1,2) = 0.0;
    Bmatrix( 1, 3 ) = 1.0f / ( 2.0f * area ) * c2;
    Bmatrix(1,4) = 0.0;
    Bmatrix( 1, 5 ) = 1.0f / ( 2.0f * area ) * c3;

    // Third row
    Bmatrix( 2, 0 ) = 1.0f / ( 2.0f * area ) * c1;
    Bmatrix( 2, 1 ) = 1.0f / ( 2.0f * area ) * b1;
    Bmatrix( 2, 2 ) = 1.0f / ( 2.0f * area ) * c2;
    Bmatrix( 2, 3 ) = 1.0f / ( 2.0f * area ) * b2;
    Bmatrix( 2, 4 ) = 1.0f / ( 2.0f * area ) * c3;
    Bmatrix( 2, 5 ) = 1.0f / ( 2.0f * area ) * b3;
}

void Femkernel::LinearTriangle::compute_stiffness_matrix()
{
    float area = _triangle->get_area();
    Ke = Bmatrix.transpose() * ( MaterialMatrix * Bmatrix );
    Ke *= area * thickness;
}

Matrix<float, 6, 6>& Femkernel::LinearTriangle::get_element_stiffness()
{
    return Ke;
}

Matrix<float, 6, 6>& Femkernel::LinearTriangle::get_element_mass()
{
    return Me;
}

Matrix<float, 3, 6>& Femkernel::LinearTriangle::get_B_matrix()
{
    return Bmatrix;
}

Matrix<float, 3, 3>& Femkernel::LinearTriangle::get_material_matrix()
{
    return MaterialMatrix;
}