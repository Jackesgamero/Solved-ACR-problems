//Autor: Jaime Martinez Gamero

#include <iostream>
#include <queue>
#include <vector>

bool resuelveCaso() {
	int n;

	std::cin >> n;
	if (n == 0) return false;

	long int sumandos; 
	std::priority_queue<long int, std::vector<long int>, std::greater<long int>> pq;
	for (int i = 0; i < n; ++i) {
		std::cin >> sumandos;
		pq.push(sumandos);
	}

	if (n == 1) std::cout << "0\n";
	else {
		long int sum = 0, s1, s2;
		
		while (!pq.empty()) {
			s1 = pq.top();
			pq.pop();

			s2 = pq.top();
			pq.pop();

			sum += s1 + s2;
			if (!pq.empty()) pq.push(s1 + s2);
		}

		std::cout << sum << '\n';
	}

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}