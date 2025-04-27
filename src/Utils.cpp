#include "Utils.hpp"

double distanza_tra_due_punti (double x_1, double y_1, double x_2, double y_2) {
	return sqrt(pow(x_2 - x_1,2) + pow(y_2 - y_1,2));
}

double area_del_triangolo (double x_1, double y_1, double x_2, double y_2, double x_3, double y_3) {
	return abs(x_1 * (y_2 - y_3) + x_2 * (y_3 - y_1) + x_3 * (y_1 - y_2)) / 2.0;
} 

// Funzioni per verificare le varie condizioni

void verifica_marker(const vector<Cell0D>& cell0Ds, const vector<Cell1D>& cell1Ds, const vector<Cell2D>& cell2Ds) {
    for (const auto& cell0D : cell0Ds) {
        if (cell0D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell0D con ID " << cell0D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell0D.Id << "è OK" << endl;
		}
    }
    for (const auto& cell1D : cell1Ds) {
        if (cell1D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell1D con ID " << cell1D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell1D.Id << "è OK" << endl;
		}
    }
    for (const auto& cell2D : cell2Ds) {
        if (cell2D.Marker < 0) {
            cout << "C'è un errore: il marker della Cell2D con ID " << cell2D.Id << " è negativo" << endl;
        }
		else {
			cout << "Il marker con ID " << cell2D.Id << "è OK" << endl;
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

void verifica_area_triangoli(const vector<Cell2D>& cell2Ds, const vector<Cell0D>& cell0Ds) {
	for (const auto& cell2D : cell2Ds) {

		Cell0D p1 = cell0Ds[cell2D.Vertices[0]];
		Cell0D p2 = cell0Ds[cell2D.Vertices[1]];
		Cell0D p3 = cell0Ds[cell2D.Vertices[2]];
        
		double area = area_del_triangolo(p1.X, p2.X, p3.X, p1.Y, p2.Y, p3.Y);  // Funzione implementata in Utils.cpp
        
		if (area <= 0) {
			cout << "C'è un errore: il triangolo con ID " << cell2D.Id << " ha area zero oppure negativa" << endl;
		} 
		else {
			cout << "Il triangolo con ID " << cell2D.Id << " ha area " << area << endl;
		}
	}
}


