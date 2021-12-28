//Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <string>

void subsecuenciaMaxima(std::string X, std::string Y) {
	size_t tam_x = X.length(), tam_y = Y.length();

	//Tamaño maximo de cada subcadena
	std::vector<std::vector<int>> Caracteres(tam_x + 1, std::vector<int>(tam_y + 1, 0));

	for (size_t i = 1; i <= tam_x; ++i){
		for (size_t j = 1; j <= tam_y; ++j){
			if (X[i - 1] == Y[j - 1]) Caracteres[i][j] = Caracteres[i - 1][j - 1] + 1;
			else Caracteres[i][j] = std::max(Caracteres[i - 1][j], Caracteres[i][j - 1]);
		}
	}

	std::cout << Caracteres[tam_x][tam_y] << '\n';
}

bool resuelveCaso() {
	std::string s1, s2;
	std::cin >> s1 >> s2;

	if (!std::cin) return false;

	subsecuenciaMaxima(s1, s2);

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}