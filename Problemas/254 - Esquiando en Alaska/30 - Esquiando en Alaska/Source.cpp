// Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>


bool resuelveCaso() {
	int N;
	std::cin >> N;

	if (N == 0) return false;

	std::vector<int> alturas, esquis;
	int aux;

	for (size_t i = 0; i < N; ++i){
		std::cin >> aux;
		alturas.push_back(aux);
	}

	for (size_t i = 0; i < N; ++i){
		std::cin >> aux;
		esquis.push_back(aux);
	}

	std::sort(alturas.begin(), alturas.end());
	std::sort(esquis.begin(), esquis.end());

	int suma = 0;

	for (size_t i = 0; i < N; ++i){
		suma += abs(alturas[i] - esquis[i]);
	}

	std::cout << suma << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
