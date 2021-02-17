//Autor : Jaime Martinez Gamero

#include <iostream>
#include <vector>

int parches(const std::vector<int>& M, const int L) {
	int nParches = M.size();
	int ini = M[0];

	for (int i = 0; i < M.size(); ++i){
		if (M[i] - ini <= L) nParches--;
		else ini = M[i];
	}
	return nParches + 1;
}

bool resuelveCaso() {
	size_t N;
	std::cin >> N;

	if (!std::cin) return false;
	
	std::vector<int> M;
	int L, pos;
	std::cin >> L;

	for (size_t i = 0; i < N; ++i){
		std::cin >> pos;
		M.push_back(pos);
	}

	std::cout << parches(M, L) << '\n';

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}