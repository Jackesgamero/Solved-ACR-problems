#include <iostream>
#include <string>
#include<map>

bool resuelveCaso() {
	int n;
	std::cin >> n;

	if (n == 0) return false;

	std::map<std::string, int> ejercicios;
	std::string nombre, resultado;

	for (size_t i = 0; i < n; ++i){
		std::cin.ignore();
		getline(std::cin, nombre);
		std::cin >> resultado;

		if (resultado == "CORRECTO")
			ejercicios[nombre]++;
		else 
			ejercicios[nombre]--;
	}

	for (auto e : ejercicios)
		if(e.second != 0)
			std::cout << e.first << ", " << e.second << "\n";

	std::cout << "---\n";

	return true;

}

int main() {
	while (resuelveCaso());
	return 0;
}