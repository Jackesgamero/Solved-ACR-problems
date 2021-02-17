//Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
    int _V;  // número de vértices
    int _A;  // número de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vértices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada.
     */
    Grafo(std::istream& flujo) {
        flujo >> _V;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v, w);
        }
    }

    /**
     * Devuelve el número de vértices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el número de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * Añade la arista v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
        _ady[w].push_back(v);
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

void dfs(const Grafo &g, std::vector<bool>&marked, int nodo, int& totalmarked) {
	marked[nodo] = true;
	totalmarked++;

	for (auto elem : g.ady(nodo))
		if (!marked[elem]) dfs(g, marked, elem, totalmarked);

}

void resuelveCaso() {
	int N;
	size_t M;
	std::cin >> N >> M;
	
	int A, B;
	Grafo g(N + 1);

	for (size_t i = 0; i < M; ++i){
		std::cin >> A >> B;
		g.ponArista(A, B);
	}

	std::vector<bool> marked(N + 1, false);
	int maxAmigos = 0, amigos;

	for (size_t i = 1; i <= N; ++i){
		amigos = 0;
		dfs(g, marked, i, amigos);
		if (amigos > maxAmigos) maxAmigos = amigos;
	}
	std::cout << maxAmigos << '\n';
}

int main() {
	int N;
	std::cin >> N;
	for (size_t i = 0; i < N; ++i) resuelveCaso();
	return 0;
}