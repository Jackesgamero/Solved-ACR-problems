#include <iostream>

int calcularAltura() {
	int hijos;
	std::cin >> hijos;

	if (hijos == 0) return 1;
	
	int altura = 1, aux;

	for (int i = 0; i < hijos; ++i){
		aux = calcularAltura();
		if (aux > altura) altura = aux;
	}

	return altura + 1;
}

bool resuelveCaso() {
	std::cout << calcularAltura() << '\n';
	return true;
}


int main() {

	int n = 0;
	std::cin >> n;

	for (int i = 0; i < n; ++i) resuelveCaso();
}