//Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

int maxComida(const std::vector<int>& Cubos, size_t N) {
	//Maxima comida a conseguir en los cubos del i al j 
	std::vector<std::vector<int>> MaxComida(N, std::vector<int>(N));

	//Caso base
	for (size_t i = 0; i < N; ++i)
		MaxComida[i][i] = Cubos[i];

	//Recorremos diagonales
	for (size_t d = 1; d < N; ++d){
		for (size_t i = 0; i < N - d; ++i){
			size_t j = i + d;
			int maxIzq, maxDer; 

			//Solo hay dos cubos
			if (j == i + 1) maxIzq = Cubos[i];

			else if (Cubos[i + 1] >= Cubos[j])  // i, i + 1 
				maxIzq = Cubos[i] + MaxComida[i + 2][j];
			else // i, j
				maxIzq = Cubos[i] + MaxComida[i + 1][j - 1];

			//Solo hay dos cubos
			if (j == i + 1) maxDer = Cubos[j];

			else if (Cubos[i] <= Cubos[j - 1]) // j, j - 1
				maxDer = Cubos[j] + MaxComida[i][j - 2];
			else // j, i
				maxDer = Cubos[j] + MaxComida[i + 1][j - 1];

			MaxComida[i][j] = std::max(maxIzq, maxDer);
		}
	}

	return MaxComida[0][N - 1];
}

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (N == 0) return false;
	
	std::vector<int> Cubos(N);

	for (size_t i = 0; i < N; ++i)
		std::cin >> Cubos[i];

	std::cout << maxComida(Cubos, N) << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}