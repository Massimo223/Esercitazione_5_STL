#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "src/Utils.hpp"
#include "src/PolygonalMesh.hpp"
#include "ExportParaview/UCDUtilities.hpp"

using namespace PolygonalLibrary;

int main() {   
	vector<Cell0D> cell0Ds;
    vector<Cell1D> cell1Ds;
    vector<Cell2D> cell2Ds;
	ifstream file_zero("Cell0Ds.csv");
	ifstream file_uno("Cell1Ds.csv");
	ifstream file_due("Cell2Ds.csv");
	string riga;
	
	// Leggo le prime righe dei file così che dopo parta dalla seconda
	
	getline(file_zero, riga);
	getline(file_uno, riga);              
	getline(file_due, riga);
	
	// Leggo le righe a partire dalla seconda
	
	while (getline(file_zero,riga)) {
		Cell0D cell_0;
		stringstream ss(riga);
		string valore;
		getline(ss, valore, ';');		
		cell_0.Id = stoi(valore);
		getline(ss, valore, ';');	
		cell_0.Marker = stoi(valore);
		getline(ss, valore, ';'); 
		valore.erase(remove(valore.begin(), valore.end(), '.'), valore.end());
		cell_0.X = stod(valore);
		getline(ss, valore, ';'); 
		valore.erase(remove(valore.begin(), valore.end(), '.'), valore.end());
		cell_0.Y = stod(valore);
		cell0Ds.push_back(cell_0);
	};
	while (getline(file_uno,riga)) {
		Cell1D cell_1;
		stringstream ss(riga);
		string valore;
		getline(ss, valore, ';'); 
		cell_1.Id = stoi(valore);
		getline(ss, valore, ';'); 
		cell_1.Marker = stoi(valore);
		getline(ss, valore, ';'); 
		cell_1.Origin = stoi(valore);
		getline(ss, valore, ';'); 
		cell_1.End = stoi(valore);
		cell1Ds.push_back(cell_1);
	};
    while (getline(file_due, riga)) {
        Cell2D cell_2;
        stringstream ss(riga);
        string valore;
        getline(ss, valore, ';'); 
		cell_2.Id = stoi(valore);
        getline(ss, valore, ';'); 
		cell_2.Marker = stoi(valore);
        getline(ss, valore, ';'); 
		cell_2.NumVertices = stoi(valore);
        for (int i = 0; i < cell_2.NumVertices; i++) {
            getline(ss, valore, ';');
            cell_2.Vertices.push_back(stoi(valore));
        }
        getline(ss, valore, ';'); 
		cell_2.NumEdges = stoi(valore);
        for (int i = 0; i < cell_2.NumEdges; i++) {
            getline(ss, valore, ';');
            cell_2.Edges.push_back(stoi(valore));
        }
		cell2Ds.push_back(cell_2);
    };
	verifica_marker(cell0Ds,cell1Ds,cell2Ds);
	verifica_lato(cell1Ds, cell0Ds);
	verifica_area_poligoni(cell2Ds, cell0Ds);
	    PolygonalMesh mesh;

    if (!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for (const auto& m : mesh.MarkerCell0Ds)
            for (const unsigned int id : m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               cell0Ds_properties);
    }

    {
        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for (const auto& m : mesh.MarkerCell1Ds)
            for (const unsigned int id : m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

		utilities.ExportSegments("./Cell1Ds.inp",
								mesh.Cell0DsCoordinates,
								mesh.Cell1DsExtrema,
								{},
								cell1Ds_properties);

    }

    {
        vector<Gedim::UCDProperty<double>> cell2Ds_properties(1);

        cell2Ds_properties[0].Label = "Marker";
        cell2Ds_properties[0].UnitLabel = "-";
        cell2Ds_properties[0].NumComponents = 1;

        vector<double> cell2Ds_marker(mesh.NumCell2Ds, 0.0);
        for (const auto& m : mesh.MarkerCell2Ds)
            for (const unsigned int id : m.second)
                cell2Ds_marker.at(id) = m.first;

        cell2Ds_properties[0].Data = cell2Ds_marker.data();

        utilities.ExportPolygons("./Cell2Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell2DsVertices,
                                 {},
                                 cell2Ds_properties);
    }
    return 0;
}
