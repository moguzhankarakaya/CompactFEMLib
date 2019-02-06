//
// Created by oguzhan on 04.07.18.
//
#include <iostream>
#include "Geokernel/Vertex.h"
#include "Geokernel/Rectangle.h"
#include "Utilities/JSonParser.hpp"

using namespace Geokernel;
using ptr_conv = std::shared_ptr<AbsGeometry>;

int main() {


    std::cout << " Read Raw Geometry ##################" << std::endl;
    JSonParser::readRawGeometry();
    JSonParser::writeMesh(3);
    std::cout << " Read Mesh ##########################" << std::endl;
    JSonParser::readMesh();

    return 0;
}