//Autor: Jaime Martinez Gamero

#include <iostream>
#include <algorithm>
#include <vector>

struct Intervalo {
	int c, f;
	Intervalo() { c = 0; f = 0; }
	Intervalo(int _c, int _f) { c = _c; f = _f; }
	bool operator <(const Intervalo& other) const {
		if (c == other.c) return f > other.f; return c < other.c;
	}
};

bool resuelveCaso() {
	size_t C, F, N;
	std::cin >> C >> F >> N;

	if (C == 0 && F == 0 && N == 0) return false;

	int c, f;
	std::vector<Intervalo> V;
	std::less<Intervalo> comparator;

	for (size_t i = 0; i < N; ++i) {

		std::cin >> c >> f;
		Intervalo In = Intervalo(c, f);
		V.push_back(In);
	}

	std::sort(V.begin(), V.end(), comparator);

	int fin = C, maximo = C, numIntervalos = 0;

	for (size_t i = 0; i < V.size() && fin < F; ++i){
		if (V[i].c > fin) { fin = maximo; ++numIntervalos; }
		if (V[i].c <= fin && V[i].f > maximo)
			maximo = V[i].f;
	}

	if (fin >= F) std::cout << numIntervalos << '\n';
	else if (maximo >= F) std::cout << numIntervalos + 1 << '\n';
	else std::cout << "Imposible\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
