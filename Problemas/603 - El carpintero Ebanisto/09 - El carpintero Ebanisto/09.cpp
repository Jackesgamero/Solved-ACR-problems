//Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1000000000;

void esfuerzoMinimo(std::vector<int> const& tabla, int& esfMin) {
    size_t N = tabla.size();
    std::vector<std::vector<int>> Esfuerzos(N, std::vector<int>(N, 0));

    //Rellena la triangular superior de la tabla
    for (size_t d = 2; d <= N - 1; ++d) // diagonales
        for (size_t i = 0; i < N - d; ++i) { // elementos de diagonal
            size_t j = i + d;
            Esfuerzos[i][j] = INF;
            for (size_t k = i + 1; k < j; ++k) 
                Esfuerzos[i][j] = std::min(Esfuerzos[i][j], Esfuerzos[i][k] + Esfuerzos[k][j] + 2 * (tabla[j] - tabla[i]));
        }

    esfMin = Esfuerzos[0][N - 1];
}

bool resuelveCaso() {
    size_t L, N;

    std::cin >> L >> N;

    if (L == 0 && N == 0) return false;

    std::vector<int> tabla(N + 2);
    tabla[0] = 0;
    tabla[N + 1] = L;

    for (size_t i = 1; i <= N; ++i) 
        std::cin >> tabla[i];

    int sol = 0;
    esfuerzoMinimo(tabla, sol);

    std::cout << sol << '\n';
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}