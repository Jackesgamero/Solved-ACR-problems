// Autor: Jaime Martinez Gamero

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

bool resuelveCaso() {
	int N;
	std::cin >> N;

	if (N == 0) return false;

	char c;
	int h, m, dur, ini;
	std::vector<std::pair<int, int>> P(N);

	for (size_t i = 0; i < N; ++i){
		std::cin >> h >> c >> m >> dur;
		ini = m + h * 60;
		P[i] = { ini, dur };
	}

	std::sort(P.begin(), P.end());
	
	int max = 24 * 60 + 10;
	std::vector<int> maxT(max + 1, 0);

	for (size_t i = 1; i < N + 1; ++i)
		for (int j = max; j > 0; --j){
			if (j >= P[i - 1].first + P[i - 1].second + 10)
				maxT[j] = std::max(maxT[j], maxT[P[i - 1].first] + P[i - 1].second);
		}

	std::cout << maxT[max] << '\n';
	
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}