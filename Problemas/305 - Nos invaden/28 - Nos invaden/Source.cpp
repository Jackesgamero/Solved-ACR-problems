// Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (!std::cin) return false;

	int aux;
	std::vector<int> Enemigos, Aliados;

	for (size_t i = 0; i < N; ++i){
		std::cin >> aux;
		Enemigos.push_back(aux);
	}
	for (size_t i = 0; i < N; ++i){
		std::cin >> aux;
		Aliados.push_back(aux);
	}

	std::sort(Enemigos.begin(), Enemigos.end(), std::greater<int>());
	std::sort(Aliados.begin(), Aliados.end(), std::greater<int>());

	int sol = 0, j = 0;
	for (size_t i = 0; i < N; ++i){
		if (Enemigos[i] <= Aliados[j]) { sol++; j++; }
	}

	std::cout << sol << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}