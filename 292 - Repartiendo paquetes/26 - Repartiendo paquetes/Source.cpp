// Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits.h>

#include <memory>
#include <stdexcept>

//
//  DigrafoValorado.h
//
//  Implementación de grafos dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

template <typename Valor>
class AristaDirigida {
public:
	AristaDirigida() : pimpl(nullptr) {}
	AristaDirigida(int v, int w, Valor valor) : pimpl(std::make_shared<AristaDirigida_impl>(v, w, valor)) {}
	int desde() const { return pimpl->v; }
	int hasta() const { return pimpl->w; }
	Valor valor() const { return pimpl->valor; }

	void print(std::ostream& o = std::cout) const {
		o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
	}

	bool operator<(AristaDirigida<Valor> const& b) const {
		return valor() < b.valor();
	}
	bool operator>(AristaDirigida<Valor> const& b) const {
		return b.valor() < valor();
	}
private:
	struct AristaDirigida_impl {
		int v, w;
		Valor valor;
		AristaDirigida_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
	};
	std::shared_ptr<AristaDirigida_impl> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, AristaDirigida<Valor> const& ar) {
	ar.print(o);
	return o;
}



template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class DigrafoValorado {
public:

	/**
	 * Crea un grafo con V vértices.
	 */
	DigrafoValorado(int v) : _V(v), _E(0), _ady(_V) {}

	/**
	 * Devuelve el número de vértices del grafo.
	 */
	int V() const { return _V; }

	/**
	 * Devuelve el número de aristas del grafo.
	 */
	int E() const { return _E; }

	/**
	 * Añade la arista dirigida v-w al grafo.
	 * @throws invalid_argument si algún vértice no existe
	 */
	void ponArista(AristaDirigida<Valor> arista) {
		int v = arista.desde(), w = arista.hasta();
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::invalid_argument("Vertice inexistente");
		++_E;
		_ady[v].push_back(arista);
	}

	/**
	 * Comprueba si hay arista de v a w.
	 */
	bool hayArista(int v, int w) const {
		for (auto a : _ady[v])
			if (a.a() == w) return true;
		return false;
	}

	/**
	 * Devuelve la lista de adyacencia de v.
	 * @throws invalid_argument si v no existe
	 */
	AdysDirVal<Valor> const& ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::invalid_argument("Vertice inexistente");
		return _ady[v];
	}

	/**
	 * Devuelve el grafo dirigido inverso.
	 */
	DigrafoValorado<Valor> inverso() const {
		DigrafoValorado inv(_V);
		for (auto v = 0; v < _V; ++v) {
			for (auto a : _ady[v]) {
				inv.ponArista({ a.hasta(), a.desde(), a.valor() });
			}
		}
		return inv;
	}

	/**
	 * Muestra el grafo en el stream de salida o
	 */
	void print(std::ostream& o = std::cout) const {
		o << _V << " vértices, " << _E << " aristas\n";
		for (auto v = 0; v < _V; ++v) {
			o << v << ": ";
			for (auto a : _ady[v]) {
				o << a << " ";
			}
			o << "\n";
		}
	}

private:
	int _V;   // número de vértices
	int _E;   // número de aristas
	std::vector<AdysDirVal<Valor>> _ady;   // vector de listas de adyacentes

};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, const DigrafoValorado<Valor>& g) {
	g.print(o);
	return o;
}


struct Casa {
	//Numero y esfuerzo acumulado
	int num, esf;
	Casa(int n, int e) {
		num = n; esf = e;
	}
	bool operator<(const Casa& other) const { 
		return other.esf < esf;
	}
};

int dijkstra(const DigrafoValorado<int>& g, int origen, int destino, std::vector<int>& distTo) {
	std::priority_queue<Casa> pq;

	distTo[origen] = 0;
	pq.push(Casa(origen, 0));

	while (!pq.empty()) {
		Casa c = pq.top();
		pq.pop();

		if (distTo[c.num] >= c.esf) 
			if (c.num == destino) return c.esf;

		for (auto a : g.ady(c.num)){
			int c2 = a.hasta();
			int esf = a.valor() + c.esf;

			if (distTo[c2] > esf) {
				distTo[c2] = esf;
				pq.push(Casa(c2, esf));
			}
		}
	}
	return -1;
}

bool resuelveCaso() {
	int N;
	std::cin >> N;

	if (!std::cin) return false;

	DigrafoValorado<int> ida(N), vuelta(N);
	size_t E;
	std::cin >> E;

	int c1, c2, esfuerzo;
	for (size_t i = 0; i < E; ++i){
		std::cin >> c1 >> c2 >> esfuerzo;
		AristaDirigida<int> a1 = AristaDirigida<int>(c1 - 1, c2 - 1, esfuerzo);
		AristaDirigida<int> a2 = AristaDirigida<int>(c2 - 1, c1 - 1, esfuerzo);
		ida.ponArista(a1);
		vuelta.ponArista(a2);
	}
	
	//Mapa de minimos esfuerzos entre los distintos caminos de las casas
	std::map<std::pair<int, int>, int> ESF;

	//Indica si hay un camino desde la oficina a todas las casas de un dia
	bool conectadas = true;

	//O -> Oficina, P -> Direcciones
	int O, P;
	std::cin >> O >> P;
	O--;

	std::vector<int> distTo(N, INT_MAX), distTo2(N, INT_MAX);
	
	//Calculamos los minimos esfuerzos para la ida desde la oficina a todas las casas
	dijkstra(ida, O, N, distTo);
	for (int i = 0; i < N; ++i) 
		ESF[std::make_pair(O, i)] = distTo[i];
		
	//Calculamos los minimos esfuerzos para la vuelta desde cada casa a la oficina
	dijkstra(vuelta, O, N, distTo2);
	for (int i = 0; i < N; ++i)
		ESF[std::make_pair(i, O)] = distTo2[i];

	int esfMinimo = 0, esf, casa;
	for (int i = 0; i < P; ++i){
		std::cin >> casa;
		casa--;

		esf = ESF[std::make_pair(O, casa)];
		if (esf == INT_MAX) conectadas = false;
		else esfMinimo += esf;

		esf = ESF[std::make_pair(casa, O)];
		if (esf == INT_MAX) conectadas = false;
		else esfMinimo += esf;
	}

	if (!conectadas) std::cout << "Imposible\n";
	else std::cout << esfMinimo << '\n';


	//Notese que si un paquete no puede ser entregado esfMinimo representa el esfuerzo
	//de entregar todos los paquetes menos el que no era posible

	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}