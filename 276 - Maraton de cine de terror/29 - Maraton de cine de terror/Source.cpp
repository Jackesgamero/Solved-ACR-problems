// Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

class Pelicula {
public:
	Pelicula() : hora(0), minuto(0), duracion(0), inicio(0), fin(0) {}

	int getInicio() const { return inicio; }
	int getFin() const { return fin; }

	bool operator <(const Pelicula& other) const {
		return fin < other.getFin();
	}
	bool operator >(const Pelicula& other) const {
		return fin > other.getFin();
	}

	void read(std::istream& i = std::cin) {
		char c;

		i >> hora;
		i >> c;
		i >> minuto;
		i >> duracion;

		inicio = (hora * 60) + minuto;
		fin = inicio + duracion;
	}
private:
		int hora;
		int minuto;
		int duracion;
		int inicio;
		int fin;
};

inline std::istream& operator>>(std::istream& i, Pelicula& a) {
	a.read(i);
	return i;
}

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (N == 0) return false;

	std::vector<Pelicula> P(N);
	for (size_t i = 0; i < N; ++i){
		std::cin >> P[i];
	}

	std::sort(P.begin(), P.end());
	int sol = 0, inicio = 0;

	for (size_t i = 0; i < N; ++i){
		if (P[i].getInicio() >= inicio) {
			sol++;
			inicio = P[i].getFin() + 10;
		}
	}
	std::cout << sol << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
