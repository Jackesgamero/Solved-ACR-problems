//Jaime Martínez Gamero
//FAL DG::Gritos en Halloween

#include <iostream>
#include <string>
using namespace std;

/*
		   | co              si n = 1
	T(n) = |
		   | T(n - 1) + c1   si n > 1
	O(n)
*/

//Devuelve la longitud de los segmentos de los extremos
long long int longitud(long long int n, long long  int k, long long int& l) {
	//Caso recursivo
	if (n > 1) {
		l = 2 * longitud(n - 1, k, l) + 2 + n;
	}
	//Casos base
	if (n == 1) { return 3; }
	if (n == 0) { l = 0; }
	return l;
}

int grito(long long int n, long long int k, long long int& l) {

	l = longitud(n, k, l);

	//Si la posicion esta en el primer segmento del grito
	if (k <= l) {
		l = 0;
		grito(n - 1, k, l);
	}
	//Si la posicion esta en el tercer segmento del grito
	else if (k > l + 3 + n) {
		k = k - l - 3 - n; l = 0;
		grito(n - 1, k, l);
	}
	//Si la posicion esta en el centro del grito
	else {
		if (k == l + 1) { l = 1; }
		else if (k == l + 3 + n) { l = 3; }
		else l = 2;
	}
	return l;
}

bool resuelveCaso() {
	long long int n, k, l = 0;
	cin >> n;
	cin >> k;
	if (!std::cin) // fin de la entrada
		return false;
	int sol = grito(n - 1, k, l);
	if (sol == 1) {
		cout << "B" << endl;
	}
	else if (sol == 3) {
		cout << "H" << endl;
	}
	else cout << "U" << endl;
	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}