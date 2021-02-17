//Autor : Jaime Martinez Gamero

#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

#include <memory>
#include <stdexcept>

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


struct calle {
    int nodo, dist, calles;
    calle(int a, int b, int c) {nodo = a; dist = b; calles = c;}

    bool operator<(const calle& other)const { 
        if (other.dist == dist) return other.calles < calles; 
        return other.dist < dist;
    }
};


int dijkstra(const GrafoValorado<int> &g, int origen, int destino, int &calles) {
    std::vector<int> distancias(g.V(), INT_MAX);
    std::priority_queue<calle> pq;

    distancias[origen] = 0;
    pq.push(calle(origen, 0, 0));
    
   
    while (!pq.empty()) {
        calle c = pq.top(); pq.pop();

        if (distancias[c.nodo] >= c.dist) {

            if (c.nodo == destino) { 
                calles = c.calles; 
                return c.dist; 
            }

            for (auto a : g.ady(c.nodo)) {
                int dest = a.otro(c.nodo);
                int distancia = a.valor() + c.dist;

                if (distancias[dest] >= distancia) {
                    distancias[dest] = distancia;
                    pq.push(calle(dest, distancia, c.calles + 1));
                }
            }
        }
    }
    return -1;
}

int bfs(const GrafoValorado<int> &g, int origen, int destino) {
    std::vector<bool> marked(g.V(), false);
    std::queue<std::pair<int, int> > q;

    marked[origen] = true;
    q.push(std::make_pair(origen, 0));

   
    while (!q.empty()) {
        std::pair<int, int> aux = q.front(); q.pop();

        if (aux.first == destino) return aux.second;

        for (auto a : g.ady(aux.first)) {
            int b = a.otro(aux.first);

            if (!marked[b]) {
                marked[b] = true;
                q.push(std::make_pair(b, aux.second + 1));
            }
        }
    }
    return -1;
}

bool resuelveCaso() {
    size_t N;
    std::cin >> N;

    if (!std::cin) return false;

    size_t C;
    std::cin >> C;
    int c1, c2, longitud;
    GrafoValorado<int> g(N);

    for (size_t i = 0; i < C; ++i){
        std::cin >> c1 >> c2 >> longitud;
        Arista<int> a = Arista<int>(c1 - 1, c2 - 1, longitud);
        g.ponArista(a);
    }

    int K, a, b, _calles = 0;
    std::cin >> K;
    for (int i = 0; i < K; ++i){
        std::cin >> a >> b;

        //Comprobamos si existe un camino para a y b
        int calles = bfs(g, a - 1, b - 1);

        if (calles == -1) std::cout << "SIN CAMINO\n";
        else {
            //Buscamos la distancia minima entre a y b
            std::cout << dijkstra(g, a - 1, b - 1, _calles) << " ";


            if (calles == _calles) std::cout << "SI\n";
            else std::cout << "NO\n";
        }
    }
    std::cout << "----\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}