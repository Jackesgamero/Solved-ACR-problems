//Autor : Jaime Martinez Gamero

#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>

#include <memory>
#include <stdexcept>

//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class IndexPQ {
public:
	// registro para las parejas < elem, prioridad >
	struct Par {
		int elem;
		T prioridad;
	};

private:
	// vector que contiene los datos (pares < elem, prio >)
	std::vector<Par> array;     // primer elemento en la posición 1

	// vector que contiene las posiciones en array de los elementos
	std::vector<int> posiciones;   // un 0 indica que el elemento no está

	/* Objeto función que sabe comparar prioridades.
	 antes(a,b) es cierto si a es más prioritario que b */
	Comparator antes;

public:
	IndexPQ(int N, Comparator c = Comparator()) : array(1), posiciones(N, 0), antes(c) {}

	IndexPQ(IndexPQ<T, Comparator> const&) = default;

	IndexPQ<T, Comparator>& operator=(IndexPQ<T, Comparator> const&) = default;

	~IndexPQ() = default;

	// e debe ser uno de los posibles elementos
	void push(int e, T const& p) {
		if (posiciones.at(e) != 0)
			throw std::invalid_argument("No se pueden insertar elementos repetidos.");
		else {
			array.push_back({ e, p });
			posiciones[e] = size();
			flotar(size());
		}
	}

	void update(int e, T const& p) {
		int i = posiciones.at(e);
		if (i == 0) // el elemento e se inserta por primera vez
			push(e, p);
		else {
			array[i].prioridad = p;
			if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
				flotar(i);
			else // puede hacer falta hundir a e
				hundir(i);
		}
	}

	int size() const {
		return int(array.size()) - 1;
	}

	bool empty() const {
		return size() == 0;
	}

	Par const& top() const {
		if (size() == 0)
			throw std::domain_error("No se puede consultar el primero de una cola vacia");
		else return array[1];
	}

	void pop() {
		if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
		else {
			posiciones[array[1].elem] = 0; // para indicar que no está
			if (size() > 1) {
				array[1] = std::move(array.back());
				posiciones[array[1].elem] = 1;
				array.pop_back();
				hundir(1);
			}
			else
				array.pop_back();
		}
	}

private:

	void flotar(int i) {
		Par parmov = std::move(array[i]);
		int hueco = i;
		while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad)) {
			array[hueco] = std::move(array[hueco / 2]); posiciones[array[hueco].elem] = hueco;
			hueco /= 2;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

	void hundir(int i) {
		Par parmov = std::move(array[i]);
		int hueco = i;
		int hijo = 2 * hueco; // hijo izquierdo, si existe
		while (hijo <= size()) {
			// cambiar al hijo derecho de i si existe y va antes que el izquierdo
			if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
				++hijo;
			// flotar el hijo si va antes que el elemento hundiéndose
			if (antes(array[hijo].prioridad, parmov.prioridad)) {
				array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
				hueco = hijo; hijo = 2 * hueco;
			}
			else break;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

};

//
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

template <typename Valor>
class Arista {
public:
	Arista() : pimpl(nullptr) {}
	Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}

	int uno() const { return pimpl->v; }
	int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
	Valor valor() const { return pimpl->valor; }

	void print(std::ostream& o = std::cout) const {
		o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
	}

	bool operator<(Arista<Valor> const& b) const {
		return valor() < b.valor();
	}
	bool operator>(Arista<Valor> const& b) const {
		return b.valor() < valor();
	}
private:
	struct Arista_impl {
		int v, w;
		Valor valor;
		Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
	};

	std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, Arista<Valor> const& ar) {
	ar.print(o);
	return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:

	/**
	 * Crea un grafo valorado con V vértices, sin aristas.
	 */
	GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }

	/**
	 * Devuelve el número de vértices del grafo.
	 */
	int V() const { return _V; }

	/**
	 * Devuelve el número de aristas del grafo.
	 */
	int A() const { return _A; }

	/**
	 * Añade una arista al grafo.
	 * @throws invalid_argument si algún vértice no existe
	 */
	void ponArista(Arista<Valor> arista) {
		int v = arista.uno(), w = arista.otro(v);
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::invalid_argument("Vertice inexistente");
		++_A;
		_ady[v].push_back(arista);
		_ady[w].push_back(arista);
	}

	/**
	 * Devuelve la lista de adyacentes de v.
	 * @throws invalid_argument si v no existe
	 */
	AdysVal<Valor> const& ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::invalid_argument("Vertice inexistente");
		return _ady[v];
	}

	/**
	 * Devuelve las aristas del grafo.
	 */
	std::vector<Arista<Valor>> aristas() const {
		std::vector<Arista<Valor>> ars;
		for (int v = 0; v < V(); ++v)
			for (auto arista : ady(v))
				if (v < arista.otro(v))
					ars.push_back(arista);
		return ars;
	}

	/**
	 * Muestra el grafo en el stream de salida o
	 */
	void print(std::ostream& o = std::cout) const {
		o << _V << " vértices, " << _A << " aristas\n";
		for (auto v = 0; v < _V; ++v) {
			o << v << ": ";
			for (auto const& w : _ady[v]) {
				o << w << " ";
			}
			o << "\n";
		}
	}

private:
	int _V;   // número de vértices
	int _A;   // número de aristas
	std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
};


/**
 * Para mostrar grafos por la salida estándar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, GrafoValorado<Valor> const& g) {
	g.print(o);
	return o;
}

class ExplorarCaminos {
public:

	ExplorarCaminos(const GrafoValorado<int>& g, int origen) : distancias(g.V(), INT_MAX), pq(g.V()), rutas(g.V()) {
		dijkstra(g, origen);
	}

	int caminos() {
		int destino = rutas.size() - 1;
		return rutas[destino];
	}

private:
	std::vector<int> distancias;
	std::vector<int> rutas;
	IndexPQ<int> pq;

	void dijkstra(const GrafoValorado<int>& g, int inicio) {
		distancias[inicio] = 0;
		rutas[inicio] = 1;
		pq.push(inicio, 0);

		while (!pq.empty()) {
			auto c1 = pq.top().elem; pq.pop();
			
			for (auto c2 : g.ady(c1)) {
				int destino = c2.otro(c1);
				
				
				if (distancias[c1] + c2.valor() < distancias[destino]) {
					distancias[destino] = distancias[c1] + c2.valor();
					rutas[destino] = rutas[c1];
					pq.update(destino, distancias[destino]);
				}
				else if (distancias[c1] + c2.valor() == distancias[destino]) {
					rutas[destino] += rutas[c1];
					pq.update(destino, distancias[destino]);
				}
			}
		}
	}

};


bool resuelveCaso() {
	int N;
	std::cin >> N;

	if (!std::cin) return false;

	size_t C;
	std::cin >> C;
	int c1, c2, longitud;
	GrafoValorado<int> g(N);

	for (size_t i = 0; i < C; ++i){
		std::cin >> c1 >> c2 >> longitud;
		g.ponArista({ c1 - 1, c2 - 1, longitud });
	}

	ExplorarCaminos e(g, 0);
	int sol = e.caminos();
	std::cout << sol << '\n';

	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}