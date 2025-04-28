#include "Utils.hpp"

double distanza_tra_due_punti (double x_1, double y_1, double x_2, double y_2) {
	return sqrt(pow(x_2 - x_1,2) + pow(y_2 - y_1,2));
}

double area_del_poligono (const vector<Cell0D>& vertici, const Cell2D& poligono) {
	 if (poligono.NumVertices < 3) {
        std::cerr << "C'è un errore: un poligono deve avere almeno 3 vertici" << std::endl;
        return 0.0;
    }
	double area = 0.0;
    for (int i = 0; i < poligono.NumVertices; ++i) {
		int j = (i + 1) % poligono.NumVertices;
        const Cell0D& p1 = vertici[poligono.Vertices[i]];
        const Cell0D& p2 = vertici[poligono.Vertices[j]];
        area += p1.X * p2.Y - p2.X * p1.Y;
    }

    return std::fabs(area) / 2.0;  
} 

// Funzioni per verificare le varie condizioni

void verifica_marker(const vector<Cell0D>& cell0Ds, const vector<Cell1D>& cell1Ds, const vector<Cell2D>& cell2Ds) {
    for (const auto& cell0D : cell0Ds) {
        if (cell0D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell0D con ID " << cell0D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell0D.Id << " è OK" << endl;
		}
    }
    for (const auto& cell1D : cell1Ds) {
        if (cell1D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell1D con ID " << cell1D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell1D.Id << " è OK" << endl;
		}
    }
    for (const auto& cell2D : cell2Ds) {
        if (cell2D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell2D con ID " << cell2D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell2D.Id << " è OK" << endl;
		}
    }
}

void verifica_lato(const vector<Cell1D>& cell1Ds, const vector<Cell0D>& cell0Ds) {
	for (const auto& cell1D : cell1Ds) {
		Cell0D origine = cell0Ds[cell1D.Origin];
		Cell0D fine = cell0Ds[cell1D.End];
        
		double lunghezza = distanza_tra_due_punti(origine.X, fine.X, origine.Y, fine.Y); // Funzione implementata in Utils.cpp
		
		if (lunghezza <= 0) {
			cout << "C'è un errore: il lato con ID " << cell1D.Id << " ha lunghezza zero oppure negativa" << endl;
		} 
		else {
			cout << "Il lato con ID " << cell1D.Id << " ha lunghezza " << lunghezza << endl;
		}
	}
}

void verifica_area_poligoni(const vector<Cell2D>& cell2Ds, const vector<Cell0D>& cell0Ds) {
    for (const auto& poligono : cell2Ds) {
        // Passa il singolo poligono (elemento del vettore) alla funzione area_del_poligono
        double area = area_del_poligono(cell0Ds, poligono);

        if (area <= 0) {
            cout << "Errore: il poligono con ID " << poligono.Id << " ha area zero o negativa" << endl;
        } else {
            cout << "Il poligono con ID " << poligono.Id << " ha area " << area << endl;
        }
    }
}
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{

bool ImportMesh(PolygonalMesh& mesh)
{
    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;
}

// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >> id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);
        mesh.Cell0DsId.push_back(id);

        // Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }
    }

    return true;
}

// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >> id >> marker >> mesh.Cell1DsExtrema(0, id) >> mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        // Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell1Ds.find(marker);
            if(it == mesh.MarkerCell1Ds.end())
            {
                mesh.MarkerCell1Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }
    }

    return true;
}

// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id, numVertices, numEdges;
        converter >> id >> numVertices;

        array<unsigned int, 8> vertices = {}; // max 8 vertici
        for (unsigned int i = 0; i < numVertices; ++i)
            converter >> vertices[i];

        converter >> numEdges;
        array<unsigned int, 8> edges = {}; // max 8 spigoli
        for (unsigned int i = 0; i < numEdges; ++i)
            converter >> edges[i];

        mesh.Cell2DsId.push_back(id);
		mesh.Cell2DsVertices.push_back(std::vector<unsigned int>(vertices.begin(), vertices.end()));
		mesh.Cell2DsEdges.push_back(std::vector<unsigned int>(edges.begin(), edges.end()));

    }

    return true;
}

}
