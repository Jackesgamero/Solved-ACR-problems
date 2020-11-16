#include <iostream>
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <set>

int siguiente(int n, const std::set<int> s) {
	int suma = 0;
	while (n > 0) {
		int d = n % 10;
		suma += d * d * d;
		n /= 10;
	}
	if (suma == 1) {
		std::cout << "- 1 -> cubifinito.\n";
	}
	else if (s.count(suma) == 1) {
		std::cout << "- " << suma << " -> no cubifinito.\n";
	}
	else std::cout << "- " << suma << " ";

	return suma;
}

bool resuelveCaso() {
	int n;

	std::cin >> n;
	if (n == 0) return false;

	if (n == 1){
		std::cout << "1 -> cubifinito.\n";
	}
	else {
		std::set<int> s;

		std::cout << n << ' ';
		while (n != 1 && s.count(n) == 0) {
			s.insert(n);
			n = siguiente(n, s);
		}
	}

	return true;
}

int main() {
	while (resuelveCaso());
}

