#include <iostream>

int calcularBecarios(int &p, int k) {
	int hijos;
	std::cin >> hijos;

	if (hijos == 0) {
		if (p < k) return 0;
		else return 1;
	}

	int becarios = 0;

	for (int i = 0; i < hijos; ++i){
		becarios += calcularBecarios(++p, k);
		p--;
	}
	return becarios;
}

bool resuelveCaso() {
	int n, p = 0;

	std::cin >> n;
	if (!std::cin) return false;

	std::cout << calcularBecarios(p, n) << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}

