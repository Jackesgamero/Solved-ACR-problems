// Autor : Jaime Martinez Gamero

#include <iostream>
#include <queue>
#include <string>

struct paciente {
	std::string nombre;
	int gravedad, turno;

	paciente(std::string _n, int _g, int _t){
		nombre = _n; gravedad = _g; turno = _t;
	}
	bool operator<(const paciente& other) const{
		if (gravedad == other.gravedad) return turno > other.turno; return gravedad < other.gravedad;
	}
};


bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (N == 0) return false;

	std::priority_queue<paciente> pq;
	std::string nombre;
	char evento;
	int grav;

	for (size_t i = 0; i < N; ++i) {
		std::cin >> evento;

		if (evento == 'A') {
			std::cout << pq.top().nombre << '\n';
			pq.pop();
		}
		else { 
			std::cin >> nombre >> grav;
			std::cin.get();
			pq.push(paciente(nombre, grav, i));
		}
	}
	std::cout << "----\n";

	return true;
}

int main() {
	while (resuelveCaso());
}