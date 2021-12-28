//Autor: Jaime Martinez Gamero 

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool resuelveCaso() {
    std::string s,_s;
    std::cin >> s;

    if (!std::cin) return false;

    _s = s;
    std::reverse(s.begin(), s.end());

    size_t N = s.length();
    std::vector<std::vector<int>> Tabla(N + 1, std::vector<int>(N + 1, 0));

    for (size_t i = 0; i <= N; ++i)
        Tabla[i][0] = 0;

    for (size_t i = 1; i <= N; ++i){
        for (size_t j = 1; j <= N; ++j){
            if (s[i - 1] == _s[j - 1]) Tabla[i][j] = Tabla[i - 1][j - 1] + 1;
            else Tabla[i][j] = std::max(Tabla[i - 1][j], Tabla[i][j - 1]);
        }
    }

    int num = N - Tabla[N][N];
    
    std::cout << num << '\n';

    return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}
