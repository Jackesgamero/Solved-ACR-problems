// Autor : Jaime Martinez Gamero

#include <iostream>
#include <queue>
#include <algorithm>

struct Edificio {
	//Extremo mas occidental
	int W;
	//Extremo mas oriental
	int E;

	bool operator <(const Edificio& other) const {
		if (W == other.W) return E > other.E; return W > other.W;
	}
};

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (N == 0) return false;

	int W, E;
	std::priority_queue<Edificio> pq;
	
	for (size_t i = 0; i < N; ++i){
		std::cin >> W >> E;
		pq.push(Edificio{ W, E });
	}

	int pasadizos = 0, tam = 0;
	while (!pq.empty()){
		pasadizos++;
		Edificio e = pq.top(); pq.pop();
		tam = e.E - 1;

		while (!pq.empty() && e.W <= tam) {
			e = pq.top();
			if (e.W <= tam) {
				tam = std::min(e.E - 1, tam);
				pq.pop();
			}
		}
	}

	std::cout << pasadizos << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
