# pragma once

using namespace std;

#include <cmath>
#include <vector>
#include <iostream>

double distanza_tra_due_punti (double x_1, double y_1, double x_2, double y_2);

class Cell0D {
public:
    int Id , Marker;
    double X , Y;
};

class Cell1D {
public:
    int Id , Marker , Origin , End;  
};

class Cell2D {
public:
    int Id , Marker , NumVertices , NumEdges;
    vector<int> Vertices;  
    vector<int> Edges;     
};

double area_del_poligono (const vector<Cell0D>& vertici, const Cell2D& poligono);

void verifica_marker(const vector<Cell0D>& cell0Ds, const vector<Cell1D>& cell1Ds, const vector<Cell2D>& cell2Ds);

void verifica_lato(const vector<Cell1D>& cell1Ds, const vector<Cell0D>& cell0Ds);

void verifica_area_poligoni(const vector<Cell2D>& cell2Ds, const vector<Cell0D>& cell0Ds);

#include "PolygonalMesh.hpp"

namespace PolygonalLibrary
{
/// Import the polygonal mesh and test if the mesh is correct
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);

/// Import the Cell0D properties from Cell0Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

/// Import the Cell1D properties from Cell1Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

/// Import the Cell2D properties from Cell2Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

}

