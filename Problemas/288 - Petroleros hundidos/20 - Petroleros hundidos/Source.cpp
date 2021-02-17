//Autor : Jaime Martinez Gamero

#include <iostream>
#include <string>

#include <vector>

//
//  ConjuntosDisjuntos.h
//
//  Implementación de estructuras de partición o conjuntos disjuntos
//  con unión por tamaño y compresión de caminos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

class ConjuntosDisjuntos {
protected:
	int ncjtos;  // número de conjuntos disjuntos
	int mayor;
	mutable std::vector<int> p;  // enlace al padre
	std::vector<int> tam;  // tamaño de los árboles
public:

	// crea una estructura de partición con los elementos 0..N-1,
	// cada uno en un conjunto, partición unitaria
	ConjuntosDisjuntos(int N) : mayor(1), ncjtos(N), p(N), tam(N, 1) {
		for (int i = 0; i < N; ++i)
			p[i] = i;
	}

	//  devuelve el representante del conjunto que contiene a a
	int buscar(int a) const {
		if (p.at(a) == a) // es una raíz
			return a;
		else
			return p[a] = buscar(p[a]);
	}

	// unir los conjuntos que contengan a a y b
	void unir(int a, int b) {
		int i = buscar(a);
		int j = buscar(b);
		if (i == j) return;
		if (tam[i] > tam[j]) { // i es la raíz del árbol más grande
			tam[i] += tam[j]; p[j] = i;
			if (cardinal(b) > mayor)
				mayor = cardinal(b);
		}
		else {
			tam[j] += tam[i]; p[i] = j;
			if (cardinal(b) > mayor)
				mayor = cardinal(b);
		}
		--ncjtos;
	}

	// devuelve si a y b están en el mismo conjunto
	bool unidos(int a, int b) const {
		return buscar(a) == buscar(b);
	}

	// devuelve el número de elementos en el conjunto de a
	int cardinal(int a) const {
		return tam[buscar(a)];
	}

	// devuelve el número de conjuntos disjuntos
	int num_cjtos() const { return ncjtos; }

	// devuelve el numero de elementos del conjunto mas grande

	int mayorC() const { return mayor; }

};

//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.

template <typename Object>
class Matriz {
public:
	// crea una matriz con fils filas y cols columnas,
	// con todas sus celdas inicializadas al valor e
	Matriz(int fils, int cols, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}

	// operadores para poder utilizar notación M[i][j]
	std::vector<Object> const& operator[](int f) const {
		return datos[f];
	}
	std::vector<Object>& operator[](int f) {
		return datos[f];
	}

	// métodos que lanzan una excepción si la posición no existe
	Object const& at(int f, int c) const {
		return datos.at(f).at(c);
	}
	Object& at(int f, int c) { // este método da problemas cuando Object == bool
		return datos.at(f).at(c);
	}

	int numfils() const { return datos.size(); }
	int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

	bool posCorrecta(int f, int c) const {
		return 0 <= f && f < numfils() && 0 <= c && c < numcols();
	}
	private:
		std::vector<std::vector<Object>> datos;
	};

void derrame(const Matriz<char>& m, ConjuntosDisjuntos& mareas_negras, int i, int j, int C) {
	
	//Arriba
	if (m.posCorrecta(i - 1, j) && m[i - 1][j] == '#')
		mareas_negras.unir(i * C + j, (i - 1) * C + j);

	//Abajo
	if (m.posCorrecta(i + 1, j) && m[i + 1][j] == '#')
		mareas_negras.unir(i * C + j, (i + 1) * C + j);

	//Izquierda
	if (m.posCorrecta(i, j - 1) && m[i][j - 1] == '#')
		mareas_negras.unir(i * C + j, i * C + j - 1);

	//Derecha
	if (m.posCorrecta(i, j + 1) && m[i][j + 1] == '#')
		mareas_negras.unir(i * C + j, i * C + j + 1);

	//Diagonal superior izquierda
	if (m.posCorrecta(i - 1, j - 1) && m[i - 1][j - 1] == '#')
		mareas_negras.unir(i * C + j, (i - 1) * C + j - 1);

	//Diagonal superior derecha
	if (m.posCorrecta(i - 1, j + 1) && m[i - 1][j + 1] == '#')
		mareas_negras.unir(i * C + j, (i - 1) * C + j + 1);

	//Diagonal inferior izquierda
	if (m.posCorrecta(i + 1, j - 1) && m[i + 1][j - 1] == '#')
		mareas_negras.unir(i * C + j, (i + 1) * C + j - 1);

	//Diagonal inferior derrecha
	if (m.posCorrecta(i + 1, j + 1) && m[i + 1][j + 1] == '#')
		mareas_negras.unir(i * C + j, (i + 1) * C + j + 1);
}


bool resuelveCaso() {

	size_t F, C;
	std::string line;
	char casilla;
	bool contaminado = false;

	std::cin >> F >> C;

	if (!std::cin) return false;

	//Descartamos el salto de linea restante en el buffer de entrada
	std::cin.ignore(1);

	Matriz<char> m(F, C);
	ConjuntosDisjuntos mareas_negras(F * C);

	for (size_t i = 0; i < F; ++i){
		getline(std::cin, line);
		for (size_t j = 0; j < C; ++j){
			m[i][j] = line[j];

			if (line[j] == '#') {
				contaminado = true;
				//Comprobamos todas las casillas adyacentes a la casilla contaminada
				derrame(m, mareas_negras, i, j, C);
			}
		}
	}

	if (contaminado) std::cout << mareas_negras.mayorC();
	else std::cout << "0";

	int N;
	std::cin >> N;

	if (N > 0) std::cout << ' ';

	int f, c;
	for (size_t i = 0; i < N; ++i){
		std::cin >> f >> c;
		f--;
		c--;

		m[f][c] = '#';
		//Comprobamos todas las casillas adyacentes a la casilla contaminada
		derrame(m, mareas_negras, f, c, C);

		std::cout << mareas_negras.mayorC();

		if (i < N - 1) std::cout << ' ';
	}
	std::cout << '\n';
	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}