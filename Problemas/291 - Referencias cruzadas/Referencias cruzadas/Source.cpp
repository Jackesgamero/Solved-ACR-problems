#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

bool resuelveCaso() {

	int n;
	std::cin >> n;
	std::cin.get();

	if (n == 0) return false;

	std::string linea, clave;
	std::map<std::string, std::vector<int>> m;

	for (size_t i = 1; i <= n; ++i){
		getline(std::cin, linea);
		std::stringstream v(linea);
		while (v >> clave) {
			for (size_t i = 0; i < clave.size(); ++i) clave[i] = tolower(clave[i]);
			if (clave.size() > 2) {
				if (m[clave].size() > 0 && m[clave][m[clave].size() - 1] != i)
					m[clave].push_back(i);
				else if (m[clave].size() == 0)
					m[clave].push_back(i);
			}
		}
	}

	for (auto& it : m) {
		std::cout << it.first;

		for (size_t i = 0; i < it.second.size(); ++i)
			std::cout << " " << it.second[i];
		std::cout << "\n";
	}

	std::cout << "----\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}