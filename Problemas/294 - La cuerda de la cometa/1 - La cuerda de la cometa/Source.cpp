//Autor : Jaime Martínez Gamero

#include <iostream>
#include <array>
#include <limits.h>
#include <algorithm>
#include <utility> 

struct sol {
	bool sol;
	long long int maneras, cuerdas, coste;
};

struct Cordel {
	long long int longitud, coste;
	bool operator<(const Cordel& other) const {
		if (other.longitud == longitud) return other.coste > coste; return (other.longitud > longitud);
	}
};

std::array<long long int, 1001> minCuerdas, minCoste, Maneras1, Maneras2;

sol HaySol(const std::array<Cordel, 1000>& Cordeles, const size_t tam, const int L) {
	sol S{ false, -1, -1, -1 };

	//Inicialización minCuerdas, minCoste
	minCuerdas.fill(INT_MAX - 1); minCuerdas[0] = 0;	
	minCoste.fill(INT_MAX); minCoste[0] = 0;

	Maneras2.fill(0); Maneras1.fill(0); Maneras1[0] = 1;

	for (size_t j = 0; j < tam; ++j) {
		int initial = Cordeles[j].longitud;
		
		for (int i = L; i >= 0; --i) {
			int currLength = i + initial;
			if (currLength <= L)
				minCuerdas[currLength] = std::min(minCuerdas[currLength], minCuerdas[i] + 1);

			if (i < initial)
				Maneras2[i] += Maneras1[i];
			else
				Maneras2[i] += Maneras1[i] + Maneras1[i - initial];
				
			if (minCoste[i] == INT_MAX || initial + i > L) continue;
			minCoste[initial + i] = std::min(minCoste[initial + i], Cordeles[j].coste + minCoste[i]);
		}
		
		Maneras1.swap(Maneras2);
		Maneras2.fill(0);
	}

	if (minCuerdas[L] != INT_MAX - 1) S.sol = true;
	S.cuerdas = minCuerdas[L];
	S.maneras = Maneras1[L];
	S.coste = minCoste[L];
	return S;
}

bool resuelveCaso() {
	size_t N; int L;
	std::cin >> N >> L;

	if (!std::cin) return false;

	std::array<Cordel, 1000> Cordeles;
	Cordeles.fill({ INT_MAX, INT_MAX });

	for (size_t i = 0; i < N; ++i) {
		std::cin >> Cordeles[i].longitud >> Cordeles[i].coste;
	}
	std::sort(Cordeles.begin(), Cordeles.end());

	sol S;
	S = HaySol(Cordeles, N, L);

	if (!S.sol) std::cout << "NO\n";
	else std::cout << "SI " << S.maneras << " " << S.cuerdas << " " << S.coste << "\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
