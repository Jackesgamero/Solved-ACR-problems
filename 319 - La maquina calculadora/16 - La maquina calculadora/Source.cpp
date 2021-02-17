// Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <queue>

int numPulsaciones(int inicial, int objetivo) {
	std::vector<bool> marked(10000, false);
	std::queue<std::pair<int, int>> q;

	//Cada par representa un numero y cuantas pulsaciones han hecho falta para llegar a el
	q.push(std::make_pair(inicial, 0));
	
	while (!q.empty()) {
		//Sacamos el primero de la cola
		std::pair<int, int> num = q.front();
		q.pop();

		//Si coincide con el numero buscado devolvemos sus pulsaciones
		if (num.first == objetivo) return num.second;
		
		//Probamos con el primer boton
		int b1 = (num.first + 1 + 10000) % 10000;
		if (!marked[b1]) {
			marked[b1] = true;
			q.push(std::make_pair(b1, num.second + 1));
		}

		//Probamos con el segundo boton
		int b2 = (num.first * 2 + 10000) % 10000;
		if (!marked[b2]) {
			marked[b2] = true;
			q.push(std::make_pair(b2, num.second + 1));
		}

		//Probamos con el tercer boton
		int b3 = num.first / 3;
		if (!marked[b3])
			q.push(std::make_pair((num.first / 3), num.second + 1));
	}

	return -1;

}

bool resuelveCaso() {

	int ini, obj;
	
	std::cin >> ini;
	if (!std::cin) return false;
	
	std::cin >> obj;

	//Busqueda en anchura
	std::cout << numPulsaciones(ini,obj) << '\n';

	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}