//Autor : Jaime Martinez Gamero

#include <iostream>
#include <queue>
#include <vector>

struct usuario {
	int num, p, sig;
	usuario() { num = 0; p = 0; sig = 0; };
	usuario(int _n, int _p, int _s) {
		num = _n; p = _p; sig = _s;
	}
	bool operator<(const usuario &other) const {
		if (other.sig == sig) return other.num < num; return (other.sig < sig);
	}
};

void resuelveCaso(size_t N) {
	std::priority_queue<usuario> pq;
	
	int num, periodo;
	for (size_t i = 0; i < N; ++i) {
		std::cin >> num >> periodo;
		pq.push(usuario{num, periodo, periodo});
	}

	int K;
	usuario u;
	std::cin >> K;

	for (size_t i = 0; i < K; ++i) {

		u = pq.top(); pq.pop();
		u.sig += u.p;

		std::cout << u.num << '\n';

		pq.push(u);
	}
	std::cout << "----\n";
}

int main() {
	size_t N;

	std::cin >> N;
	while (N != 0) {
		resuelveCaso(N);
		std::cin >> N;
	}
}