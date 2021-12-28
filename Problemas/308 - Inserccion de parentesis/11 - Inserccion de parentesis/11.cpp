// Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <string>

struct decision {
	int pos;
	char r1, r2;
};

bool parentesis(std::string cadena) {
	size_t N = cadena.size() - 1;
	std::vector<std::vector<bool>> A(N + 1, std::vector<bool>(N + 1)), B(N + 1, std::vector<bool>(N + 1)), C(N + 1, std::vector<bool>(N + 1));
	
	for (size_t i = 1; i <= N; ++i){
		A[i][i] = (cadena[i] == 'a');
		B[i][i] = (cadena[i] == 'b');
		C[i][i] = (cadena[i] == 'c');
	}
	
	for (size_t d = 1; d <= N - 1; ++d){
		for (size_t i = 1; i <= N - d; ++i){
			size_t j = i + d;
			A[i][j] = false; size_t k = i;
			while (!A[i][j] && k < j) {
				if (A[i][k] && C[k + 1][j])
					A[i][j] = true;
				else if (B[i][k] && C[k + 1][j])
					A[i][j] = true;
				else if (C[i][k] && A[k + 1][j])
					A[i][j] = true;
				else
					k++;
			}
			B[i][j] = false; k = i;
			while (!B[i][j] && k < j) {
				if (A[i][k] && A[k + 1][j])
					B[i][j] = true;
				else if (A[i][k] && B[k + 1][j])
					B[i][j] = true;
				else if (B[i][k] && B[k + 1][j])
					B[i][j] = true;
				else
					k++;
			}
			C[i][j] = false; k = i;
			while (!C[i][j] && k < j) {
				if (B[i][k] && A[k + 1][j])
					C[i][j] = true;
				else if (C[i][k] && B[k + 1][j])
					C[i][j] = true;
				else if (C[i][k] && C[k + 1][j])
					C[i][j] = true;
				else k++;
			}
		}
	}

	return A[1][N];
}

bool resuelveCaso() {
	std::string cadena;
	std::cin >> cadena;

	cadena = " " + cadena;

	if (!std::cin) return false;

	bool posible = parentesis(cadena);

	if (posible) std::cout << "SI\n";
	else std::cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}