#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Cell0D {
public:
    int Id;
    int marker;
    double X , Y;
};

class Cell1D {
public:
    int Id;
    int marker;
    int origin; 
    int end;    
};

class Cell2D {
public:
    int Id;
    int Marker;
    int NumVertices;
	vector<int> Vertices;  
    int NumEdges;
	vector<int> Edges;     
};

int main()
{   
	vector<Cell0D> cell0Ds;
    vector<Cell1D> cell1Ds;
    vector<Cell2D> cell2Ds;
	ifstream file_zero("Cell0Ds.csv")
	ifstream file_uno("Cell1Ds.csv")
	ifstream file_due("Cell2Ds.csv")
	string riga;
	vector<string> vettore_righe_0;
	while (getline(file_zero,riga)) {
		Cell0d cell0;
		stringstream ss(riga);
		string valore;
		getline(ss, valore, ';'); cell_0.Id = stoi(value);
		getline(ss, valore, ';'); cell_0.marker = stoi(value);
		getline(ss, valore, ';'); cell_0.X = stod(value);
		getline(ss, valore, ';'); cell_0.Y = stod(value)
		cell0Ds.push_back(cell_0);
		}
		
	
    return 0;
}
