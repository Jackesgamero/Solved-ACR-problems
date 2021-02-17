//Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <queue>

//El TAD de los grafos da problemas en este ejercicio
struct Grafo {
	int vertices;
	std::vector<std::vector<int>> ady;

	Grafo(int v) : vertices{ v }, ady(v) {}
};

void dfs(const Grafo& grafo, std::vector<bool>&marked, std::vector<int>& ultimo, bool& ciclo, int vertice) {
	marked[vertice] = true;

	if (!ciclo) {
		for (int nodoAdy : grafo.ady[vertice]) {
			if (!marked[nodoAdy]) {
				ultimo[nodoAdy] = vertice;
				dfs(grafo, marked, ultimo, ciclo, nodoAdy);
			}
			else if (marked[nodoAdy] && ultimo[vertice] != nodoAdy) ciclo = true;
		}
	}
}

bool ArbolLibre(const Grafo& grafo) {
	//Vector con booleanos para saber que nodos estan conectados por un camino 
	std::vector<bool> marked(grafo.vertices, false);
	//Vector con los ultimos nodos que visitaron cada nodo
	std::vector<int> ultimo(grafo.vertices);
	int Origen = 0;
	bool ciclo = false;

	dfs(grafo, marked, ultimo, ciclo, Origen);

	if (ciclo) return false;
	else {
		for (bool conectado : marked) {
			if (!conectado) return false;
		}
		return true;
	}
}

bool resuelveCaso() {
	int V, A;
	std::cin >> V;

	if (!std::cin) return false;

	std::cin >> A;

	Grafo g(V);
	int v1, v2;
	for (size_t i = 0; i < A; ++i){
		std::cin >> v1 >> v2;
		g.ady[v1].push_back(v2);
		g.ady[v2].push_back(v1);
	}

	if (ArbolLibre(g)) std::cout << "SI\n";
	else std::cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}