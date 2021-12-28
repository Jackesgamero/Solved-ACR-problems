//Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1000000000;

void Floyd(std::vector<std::vector<int>>& Caminos, size_t N) {
	for (size_t k = 0; k < N; ++k)
		for (size_t i = 0; i < N; ++i)
			for (size_t j = 0; j < N; ++j)
				Caminos[i][j] = std::min(Caminos[i][j], Caminos[i][k] + Caminos[k][j]);
}

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (!std::cin) return false;

	std::vector<std::vector<int>> Caminos(N, std::vector<int>(N, INF));

	int camino;

	for (size_t i = 0; i < N - 1; ++i)
		for (size_t j = i; j < N; ++j){
			//Ir de un poblado a si mismo no tiene coste
			if (i == j) Caminos[i][i] = 0; 
			else {
				std::cin >> camino;
				Caminos[i][j] = camino;
			}
		}

	Caminos[N - 1][N - 1] = 0;
	//Calcular caminos minimos
	Floyd(Caminos, N);

	//mostramos la mitad superior de la tabla

	for (size_t i = 0; i < N; ++i){
		for (size_t j = i + 1; j < N; ++j){
			if (j < N - 1)
				std::cout << Caminos[i][j] << " ";
			else std::cout << Caminos[i][j];
		}
		if (i < N - 1) std::cout << '\n';
	}
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}