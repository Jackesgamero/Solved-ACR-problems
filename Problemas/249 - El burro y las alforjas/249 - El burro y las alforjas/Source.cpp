#include <iostream>
#include <vector>

void resuelveCaso() {
	std::vector<int> Peso(20000, 0);
	size_t burros, sacos;

	std::cin >> burros >> sacos;

	int saco;
	for (size_t i = 0; i < sacos; ++i){
		std::cin >> saco;
		Peso[saco - 1]++;
	}

	int sol = 0;
	for (int i = 0; i < 20000 && sol < burros; ++i) {
		if (Peso[i] > 0) {
			while (Peso[i] > 1 && sol < burros) {
				sol++;
				Peso[i] -= 2;
			}
		}
	}
	std::cout << sol << '\n';
}

int main() {
	int n;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i) resuelveCaso();
	return 0;
}