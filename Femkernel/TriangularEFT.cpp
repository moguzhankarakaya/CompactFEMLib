//
// Created by oguzhan on 04.09.18.
//

#include <iostream>
#include <utility>
#include "TriangularEFT.h"

Femkernel::TriangularEFT::TriangularEFT() = default;

void Femkernel::TriangularEFT::register_element(Geokernel::Types::AbsGeometryPointer key,
                                                Femkernel::Types::ElementFreedoms *value)
{
    auto newPair = new ElementFreedomPair;
    newPair->_key = key;
    newPair->_value = value;
    _triangularEFT.emplace_back(newPair);
}

Femkernel::Types::ElementFreedomsRef Femkernel::TriangularEFT::get_element(Geokernel::Types::AbsGeometryPointer key)
{
    Femkernel::Types::ElementFreedoms *returnValue = nullptr;
    for(auto &it : _triangularEFT)
    {
        if (it->_key.get() == key.get())
            returnValue = it->_value;
    }

    if(returnValue == nullptr)
        throw("Given element doesn't exist in EFT.");
    else
        return *returnValue;
}
