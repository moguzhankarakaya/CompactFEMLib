//
// Created by oguzhan on 05.11.18.
//

#include <vector>
#include <array>
#include <memory>

#ifndef ANDROIDBASEDFEM_TYPES_H
#define ANDROIDBASEDFEM_TYPES_H

#endif //ANDROIDBASEDFEM_TYPES_H

namespace Postprocessing
{
    namespace Types
    {

        typedef const std::array<float, 8> ConstPostProcessedData;
        typedef std::array<float, 8> PostProcessedData;
        typedef const std::array<float, 8>& ConstPostProcessedDataRef;
        typedef std::array<float, 8>& PostProcessedDataRef;
    }
}