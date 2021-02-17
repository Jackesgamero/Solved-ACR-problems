//Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

void resuelveCaso() {
	size_t N, V;
	std::cin >> N >> V;

	int voltaje;
	std::vector<int> Voltajes;
	
	for (size_t i = 0; i < N; ++i){
		std::cin >> voltaje;
		Voltajes.push_back(voltaje);
	}

	std::sort(Voltajes.begin(), Voltajes.end());
	int coches = 0, ini = 0, fin = Voltajes.size() - 1;

	while (ini < fin) {
		if (Voltajes[ini] + Voltajes[fin] >= V) { 
			ini++; fin--; coches++; 
		}
		else ini++;
	}
	std::cout << coches << '\n';
}

int main() {
	size_t N;
	std::cin >> N;
	for (size_t i = 0; i < N; ++i) 
		resuelveCaso();
}
