//Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

struct Cofre {
	int profundidad, oro;
	bool rescatado;
};

bool resuelveCaso() {
	size_t T;
	int N;
	std::cin >> T >> N;

	if (!std::cin) return false;

	std::vector<Cofre> Cofres(N);
	for (int i = 0; i < N; ++i){
		std::cin >> Cofres[i].profundidad >> Cofres[i].oro;
		Cofres[i].rescatado = false;
	}

	std::vector<std::vector<int>> TablaOro(N + 1, std::vector<int>(T + 1, 0));
	for (int i = 0; i < N + 1; ++i)
		TablaOro[i][0] = 0;

	for (int i = 1; i < N + 1; ++i){
		for (size_t j = 1; j < T + 1; ++j){
			if (3 * Cofres[i - 1].profundidad > j) TablaOro[i][j] = TablaOro[i - 1][j];
			else TablaOro[i][j] = std::max(TablaOro[i - 1][j], TablaOro[i - 1][j - 3 * Cofres[i - 1].profundidad] + Cofres[i - 1].oro);
		}
	}

	int k = T, cofres = 0;
	for (int i = N; i > 0; --i){
		if (TablaOro[i][k] != TablaOro[i - 1][k]) {
			cofres++;
			Cofres[i - 1].rescatado = true;
			k -= 3 * Cofres[i - 1].profundidad;
		}
	}

	std::cout << TablaOro[N][T] << '\n';
	std::cout << cofres << '\n';
	for (int i = 0; i < N; i++)
		if (Cofres[i].rescatado)
			std::cout << Cofres[i].profundidad << " " << Cofres[i].oro << '\n';
	std::cout << "----" << '\n';
	
	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}