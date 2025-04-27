# pragma once

using namespace std;

#include <cmath>
#include <vector>
#include <iostream>

double distanza_tra_due_punti (double x_1, double y_1, double x_2, double y_2);

double area_del_triangolo (double x_1, double y_1, double x_2, double y_2, double x_3, double y_3);

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

void verifica_marker(const vector<Cell0D>& cell0Ds, const vector<Cell1D>& cell1Ds, const vector<Cell2D>& cell2Ds);

void verifica_lato(const vector<Cell1D>& cell1Ds, const vector<Cell0D>& cell0Ds);

void verifica_area_triangoli(const vector<Cell2D>& cell2Ds, const vector<Cell0D>& cell0Ds);

