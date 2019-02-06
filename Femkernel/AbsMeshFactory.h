//
// Created by oguzhan on 05.07.18.
//

#ifndef FEMPACKAGE_ABSMESHFACTORY_H
#define FEMPACKAGE_ABSMESHFACTORY_H

#include "AbsMesher.h"

namespace Femkernel {

    class AbsMeshFactory
    {

    public:

        virtual void register_mesher(AbsMesher* mesher) = 0;

    private:

    };

}

#endif //FEMPACKAGE_ABSMESHFACTORY_H
