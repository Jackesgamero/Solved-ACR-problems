//Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <queue>

struct casilla {
	int num, movimientos;
	casilla() : num(0), movimientos(0) {}
	casilla(int _num, int _movimientos) : num(_num), movimientos(_movimientos) {}
};

bool resuelveCaso() {
	size_t N, K, S, E;
	std::cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && S == 0 && E == 0) return false;

	//Lista de adyacencia del grafo
	std::vector<std::vector<int>> g(N * N, std::vector<int>());
	//Vector de visitados
	std::vector<bool> marked(N * N, false);
	//Vector de serpientes y escaleras
	std::vector<int> snakes_Ladders(N * N);

	for (size_t i = 0; i < N * N; ++i) {
		snakes_Ladders[i] = i;
		for (size_t j = 1; j <= K; ++j) {
			if (N * N > i + j)
				g[i].push_back(i + j);
		}
	}

	int ini, dest;
	for (size_t i = 0; i < S + E; ++i) {
		std::cin >> ini >> dest;
		snakes_Ladders[ini - 1] = dest - 1;
	}

	casilla fin(N * N - 1, 0), c, aux = casilla();
	std::deque<casilla> bfs;

	bfs.push_back(aux);
	marked[0] = true;
	c = bfs.front();

	bool victoria = (c.num == fin.num);
	while (!victoria) {
		int num = bfs.front().num, movimientos = bfs.front().movimientos + 1;
		for (size_t i = 0; i < g[num].size() && !victoria; ++i) {
			if (!marked[g[num][i]]) {
				int n = g[num][i];
				c = casilla(snakes_Ladders[n], movimientos);

				marked[n] = true;
				marked[snakes_Ladders[n]] = true;
				bfs.push_back(c);
			}
		}
		bfs.pop_front();
		victoria = (c.num == fin.num);
	}

	std::cout << c.movimientos << '\n';
	return true;
}




int main() {
	while (resuelveCaso());
	return 0;
}