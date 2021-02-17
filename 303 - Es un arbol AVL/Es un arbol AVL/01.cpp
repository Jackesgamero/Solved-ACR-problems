//Autor : Jaime Martinez Gamero

#include <iostream>
#include <algorithm>
#include <limits.h>

bool arbolAVL(int raiz, int& minimo, int& maximo, int& altura) {
	if (raiz == -1) { maximo = 0; altura = 0; minimo = INT_MAX; return true;}
	else {
		int hijoIz, hijoDer, minIz, minDer, maxIz, maxDer, altIz, altDer;
		bool avlIzq, avlDer;

		std::cin >> hijoIz;

		//Comprobamos el hijo izquierdo
		avlIzq = arbolAVL(hijoIz, minIz, maxIz, altIz);
		
		std::cin >> hijoDer;

		//Comprobamos el hijo derecho
		avlDer = arbolAVL(hijoDer, minDer, maxDer, altDer);

		//La raiz del arbol es mayor que el maximo de los elementos del hijo izquierdo y menor que el minimo de los del derecho solo si es AVL
		minimo = std::min(raiz, minIz);
		maximo = std::max(raiz, maxDer);
		altura = std::max(altIz, altDer) + 1;
		return avlIzq && avlDer && (abs(altIz - altDer) <= 1) && (maxIz < raiz && minDer > raiz);
	}
}

void resuelveCaso() {

	bool AVL = false;
	int raiz, minimo, maximo, altura;

	std::cin >> raiz;

	AVL = arbolAVL(raiz, minimo, maximo, altura);

	if (AVL) std::cout << "SI\n";
	else std::cout << "NO\n";
}

int main() {
	int n;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i){
		resuelveCaso();
	}
}