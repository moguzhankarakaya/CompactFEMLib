#include <iostream>
#include "Geokernel/Vertex.h"
#include "Geokernel/Edge.h"
#include "Geokernel/Rectangle.h"
#include "Geokernel/Triangle.h"
#include "Geokernel/ConvexHull.h"
#include "Utilities/Bithacks.h"
#include "Geokernel/GeometryTypes.h"

using namespace Geokernel;
using ptr_conv = std::shared_ptr<AbsGeometry>;

PrimaryUtilities::Indexer idx_5(5, 5);
PrimaryUtilities::Indexer idx_4(4, 4);

void seperator(bool newLine = false)
{
    if(newLine) std::cout << std::endl;
    std::cout << std::string(15, '*') << std::endl;
}

int main() {

    std::cout << "Edge Class Test" << std::endl;
    std::cout << "Reverse Vertex Input Test: " << std::endl;
    Edge anEdge(Vertex(1,1), Vertex(0,0));
    anEdge.print_stream_out();
    std::cout << "Test Successful!" << std::endl;
    seperator();

    float delta_x = 1.5;
    float delta_y = 1.5;

    Types::VertexContainer aVertexContainer;


    for(size_t i = 0; i < 5; i++)
    {
        for(size_t j = 0; j < 5; j++)
        {
            aVertexContainer.emplace_back(Vertex(i*delta_x, j*delta_y));
        }
    }

    Types::EdgeContainer anEdgeContainer;

    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            Edge edge_1(aVertexContainer[idx_5.get_index(i, j)], aVertexContainer[idx_5.get_index(i,   j+1)]);
            Edge edge_2(aVertexContainer[idx_5.get_index(i, j)], aVertexContainer[idx_5.get_index(i+1,   j)]);
            Edge edge_3(aVertexContainer[idx_5.get_index(i, j)], aVertexContainer[idx_5.get_index(i+1, j+1)]);
            anEdgeContainer.push_back(edge_1);
            anEdgeContainer.push_back(edge_2);
            anEdgeContainer.push_back(edge_3);
        }
    }

    if(anEdgeContainer[0].is_on_edge(Vertex(0, 1)))      std::cout << "Test Successful!  ~ " << std::endl;
    if(anEdgeContainer[1].is_on_edge(Vertex(1, 0)))      std::cout << "Test Successful!  ~ " << std::endl;
    if(anEdgeContainer[2].is_on_edge(Vertex(1, 1)))      std::cout << "Test Successful!  ~ " << std::endl;
    if(!anEdgeContainer[2].is_on_edge(Vertex(0, 0)))     std::cout << "Test Successful!  ~ " << std::endl;
    if(!anEdgeContainer[2].is_on_edge(Vertex(1.6, 1.6))) std::cout << "Test Successful!  ~ " << std::endl;

    anEdgeContainer[0].divide_edge(5);
    anEdgeContainer[1].divide_edge(5);
    anEdgeContainer[2].divide_edge(5);

    anEdgeContainer[0].divide_edge(2);
    anEdgeContainer[1].divide_edge(2);
    anEdgeContainer[2].divide_edge(2);

    try{ anEdgeContainer[0].divide_edge(Vertex(1.10, 0));   } catch(const char* s){ std::cout << s << std::endl; }
    try{ anEdgeContainer[0].divide_edge(Vertex(0, 1.10));   } catch(const char* s){ std::cout << s << std::endl; }
    try{ anEdgeContainer[0].divide_edge(Vertex(0, 1.60));   } catch(const char* s){ std::cout << s << std::endl; }
    try{ anEdgeContainer[2].divide_edge(Vertex(1.10,1.10)); } catch(const char* s){ std::cout << s << std::endl; }
    try{ anEdgeContainer[2].divide_edge(Vertex(1.20,1.10)); } catch(const char* s){ std::cout << s << std::endl; }
    try{ anEdgeContainer[2].divide_edge(Vertex(1.60,1.60)); } catch(const char* s){ std::cout << s << std::endl; }

    seperator(true);
    Rectangle testRectangle_1(aVertexContainer[idx_5.get_index(1,1)], aVertexContainer[idx_5.get_index(0,0)]);
    //testRectangle_1.print_stream_out();
    Types::VertexQuad aVertexQuad;
    int index = 0;
    for(size_t i = 2; i > 0; i--)
    {
        for (size_t j = 2; j > 0; j--)
        {
            aVertexQuad[index] = aVertexContainer[idx_5.get_index(i - 1, j - 1)];
            index++;
        }
    }
    Rectangle testRectangle_2(aVertexQuad);
    seperator(true);
    //testRectangle_2.print_stream_out();
    seperator();

    std::vector<Rectangle> aRectangleContainer;

    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            aRectangleContainer.emplace_back(aVertexContainer[idx_5.get_index(i  , j   )],
                                             aVertexContainer[idx_5.get_index(i+1, j+1)]);
        }
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if( aRectangleContainer[idx_4.get_index(i, j)].isInside(Vertex( (i)     * delta_x / 2, (j)     * delta_y / 2 )))
                std::cout << "Test Successful!  ~ " << std::endl;;
            if(!aRectangleContainer[idx_4.get_index(i, j)].isInside(Vertex( (i + 4) * delta_x / 2, (j + 4) * delta_y / 2 )))
                std::cout << "Test Successful!  ~ " << std::endl;
        }
    }


    //TODO: Add tests for is inside, and add tests for Triangle

    Types::GeometryContainer geometryContainer;

    geometryContainer.emplace_back(std::make_shared<Rectangle>(aVertexContainer[idx_5.get_index(0,0)],
                                                               aVertexContainer[idx_5.get_index(2,1)]));
    geometryContainer.emplace_back(std::make_shared<Rectangle>(aVertexContainer[idx_5.get_index(4,2)],
                                                               aVertexContainer[idx_5.get_index(2,1)]));
    geometryContainer.emplace_back(std::make_shared<Triangle>(aVertexContainer[idx_5.get_index(2,0)],
                                                              aVertexContainer[idx_5.get_index(2,1)],
                                                              aVertexContainer[idx_5.get_index(3,1)]));
    geometryContainer.emplace_back(std::make_shared<Triangle>(aVertexContainer[idx_5.get_index(2,1)],
                                                              aVertexContainer[idx_5.get_index(2,2)],
                                                              aVertexContainer[idx_5.get_index(1,1)]));

    Types::VertexContainer fullGeometryVertexSet;
    Types::VertexContainer convexHullCloud;

    for(const auto &it : geometryContainer)
    {
        it->get_vector_vertex(fullGeometryVertexSet);
    }

    ConvexHull convexHull = ConvexHull(fullGeometryVertexSet);
    convexHull.calculate_convex_hull();
    convexHull.stream_convex_hull();
    convexHullCloud = convexHull.get_convex_hull();

    return 0;
}