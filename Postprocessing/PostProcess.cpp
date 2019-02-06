//
// Created by oguzhan on 05.11.18.
//

#include "PostProcess.h"

Postprocessing::PostProcessor::PostProcessor(
        Geokernel::Types::GeometryContainerRef elements,
        Femkernel::TriangularEFT& eft,
        SparseVector<float>& displacement,
        float E, float nu, float rho, float thickness
        ) : _elements(elements),
            _eft(eft),
            _displacements(displacement),
            _E(E), _nu(nu), _rho(rho), _thickness(thickness)
{

}

void Postprocessing::PostProcessor::get_element_displacements(
        Vector6fRef element_displacements,
        Femkernel::Types::ElementFreedomsRef elementFreedoms)
{
    for (int i = 0; i < 6; i++)
    {
        try {
            element_displacements[i] = _displacements.coeff(elementFreedoms[i] - 1);
        }
        catch (const std::exception &ex) {
            throw ex;
        }
        catch (...) {
            std::cout << "Error occurred while accessing displacement vector.";
            return;
        }
    }
}
void Postprocessing::PostProcessor::post_process()
{
    Matrix6f B_matrix;
    Matrix3f material_matrix;
    Vector6f element_displacements;
    Femkernel::Types::ElementFreedoms elementFreedoms;

    for(auto &element : _elements)
    {
        Femkernel::LinearTriangle linearTriangleElement( element, _E, _nu, _rho, _thickness );
        B_matrix = linearTriangleElement.get_B_matrix();
        material_matrix = linearTriangleElement.get_material_matrix();
        elementFreedoms = _eft.get_element(element);
        get_element_displacements(element_displacements, elementFreedoms);
        _strains  = B_matrix * element_displacements;
        _stresses = material_matrix * _strains;
        float vonMises = std::sqrt( ( (_stresses[0] -_stresses[1])*(_stresses[0] -_stresses[1]) +
                                      (_stresses[1])*(_stresses[1]) +
                                      (_stresses[0])*(_stresses[0]) +
                                      (6*_stresses[2]*_stresses[2]) ) / 2.0f );

        float vonMisesStrain = 2.0/3.0 * std::sqrt( 3.0 / 2.0 * ( _strains[0]*_strains[0] + _strains[1] * _strains[1] ) + 3.0 / 4.0 * _strains[2]*_strains[2] );


        auto newPair = new PostProcessedDataPair;

        auto postProcessedDataPoint = new  Postprocessing::Types::PostProcessedData{_strains[0],_strains[1],_strains[2],
                                                                                    _stresses[0],_stresses[1],_stresses[2],
                                                                                    vonMises, vonMisesStrain };
        newPair->_key = element;
        newPair->_value = postProcessedDataPoint;

        _postProcessedDataTable.emplace_back(newPair);

    }
}

Postprocessing::Types::PostProcessedDataRef
    Postprocessing::PostProcessor::get_post_processed_result(
                    Geokernel::Types::AbsGeometryPointer key)
{
    Postprocessing::Types::PostProcessedData *returnValue = nullptr;
    for(auto &it : _postProcessedDataTable)
    {
        if (it->_key.get() == key.get())
            returnValue = it->_value;
    }

    if(returnValue == nullptr)
        throw("Given element doesn't exist in Post Processed Data table.");
    else
        return *returnValue;
}
