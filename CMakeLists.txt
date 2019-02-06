cmake_minimum_required(VERSION 3.9)
project(FEMPackage)

set(CMAKE_CXX_STANDARD 17)

SET (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} $ENV{LDFLAGS})

add_library(PsProcess_lib SHARED
        Postprocessing/PostProcess.h
        Postprocessing/PostProcess.cpp
        Postprocessing/Types.h)

add_executable(Postprocessing
        Postprocessing/PostProcess.cpp
        Postprocessing/PostProcess.h
        Postprocessing/Types.h
        Postprocessing_Test.cpp)

target_link_libraries(Postprocessing Femkernel_lib)
target_link_libraries(Postprocessing Geokernel_lib)
target_link_libraries(Postprocessing Utilities_lib)

add_library(Femkernel_lib SHARED
        Femkernel/AbsMeshFactory.h
        Femkernel/AbsMesher.h
        Femkernel/AbsMeshFactory.cpp
        Femkernel/AbsMesher.cpp
        Femkernel/Mesher2D.h
        Femkernel/Mesher2D.cpp
        Femkernel/MeshFactory2D.h
        Femkernel/MeshFactory2D.cpp
        Femkernel/LinearTriangle.cpp
        Femkernel/LinearTriangle.h
        Femkernel/Assembler.h
        Femkernel/Assembler.cpp
        Femkernel/TriangularEFT.cpp
        Femkernel/TriangularEFT.h
        Femkernel/Types.h)

add_executable(Femkernel
        Femkernel_Test.cpp
        Femkernel/AbsMeshFactory.h
        Femkernel/AbsMesher.h
        Femkernel/AbsMeshFactory.cpp
        Femkernel/AbsMesher.cpp
        Femkernel/Mesher2D.h
        Femkernel/Mesher2D.cpp
        Femkernel/MeshFactory2D.h
        Femkernel/MeshFactory2D.cpp
        Femkernel/LinearTriangle.cpp
        Femkernel/LinearTriangle.h
        Femkernel/Assembler.h
        Femkernel/Assembler.cpp
        Femkernel/TriangularEFT.cpp
        Femkernel/TriangularEFT.h
        Femkernel/Types.h)

target_link_libraries(Femkernel Geokernel_lib)
target_link_libraries(Femkernel Utilities_lib)

add_library(Geokernel_lib SHARED
        Geokernel/AbsGeometry.h
        Geokernel/Rectangle.cpp
        Geokernel/Rectangle.h
        Geokernel/Vertex.cpp
        Geokernel/Vertex.h
        Geokernel/Edge.cpp
        Geokernel/Edge.h
        Geokernel/ProblemType.cpp
        Geokernel/ProblemType.h
        Geokernel/PrimaryTypes.h
        Geokernel/Triangle.cpp
        Geokernel/Triangle.h
        Geokernel/AbsGeometryElement.h
        Geokernel/ConvexHull.cpp
        Geokernel/ConvexHull.h
        Geokernel/GeometryTypes.h)

add_executable(Geokernel
        Geokernel_Test.cpp
        Geokernel/AbsGeometry.h
        Geokernel/Rectangle.cpp
        Geokernel/Rectangle.h
        Geokernel/Vertex.cpp
        Geokernel/Vertex.h
        Geokernel/Edge.cpp
        Geokernel/Edge.h
        Geokernel/ProblemType.cpp
        Geokernel/ProblemType.h
        Geokernel/PrimaryTypes.h
        Geokernel/Triangle.cpp
        Geokernel/Triangle.h
        Geokernel/AbsGeometryElement.h
        Geokernel/ConvexHull.cpp
        Geokernel/ConvexHull.h
        Geokernel/GeometryTypes.h)

target_link_libraries(Geokernel Utilities_lib)

add_library(Utilities_lib SHARED
        Utilities_Test.cpp
        Utilities/Bithacks.h
        Utilities/Json.hpp)

add_executable(Utilities
        Utilities_Test.cpp
        Utilities/Bithacks.h
        Utilities/Json.hpp)
