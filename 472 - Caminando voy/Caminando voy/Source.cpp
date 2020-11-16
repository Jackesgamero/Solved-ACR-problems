#include <iostream>
#include <vector>
#include <algorithm>

/*
* 
{ 1 <= N <= 200000 && 0 <= D <= 1000000 }
fun caminandoVoy(V[0,..N) : ent, N : ent, D : ent) dev (r : ent)
{ r = max a, b : 0 <= a <= b < N && mayor(V, a, b) > D : b - a }

mayor(V, a, b) = {Σ i : a <= i <= b : V[i] }

I = n < N && r = max a, b : 0 <= a <= b < n && mayor(V, a, b) > D : b - a
C = N - n

*/

int caminandoVoy(const std::vector<int> V, const int D, const int N) {
	int n = 0, r = 0, s = 0, a = 0;

	if (N == 1) return 0;
	
	while(n != N - 1) {
		if (V[n] < V[n + 1]) a += V[n + 1] - V[n];
		else a = 0;

		if (a <= D) s = n + 1;

		r = std::max(r, n + 1 - s);
		n++;
	}
	
	return r;
}

bool resuelveCaso() {
	std::vector<int> V;
	int aux, N, D, sol;

	std::cin >> D >> N;

	if (!std::cin) return false;

	for (size_t i = 0; i < N; ++i){
		std::cin >> aux;
		V.push_back(aux);
	}

	sol = caminandoVoy(V, D, N);

	if (sol == 0) std::cout << "APTA\n";
	else std::cout << "NO APTA\n";

	return true;
}



int main() {
	while (resuelveCaso());
	return 0;
}