#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include "src/Utils.hpp"

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
		cell_0.X = stod(valore);
		getline(ss, valore, ';'); 
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
	verifica_area_triangoli(cell2Ds, cell0Ds);
    return 0;
}
