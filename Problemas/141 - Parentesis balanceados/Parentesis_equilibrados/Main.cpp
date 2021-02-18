#include <iostream>
#include <string>
#include <stack>

bool equilibrado(std::stack<char> &pila) {
	char last = pila.top();
	pila.pop();

	if (pila.empty()) return false;

	else if (last == ']' && pila.top() == '[') {
		pila.pop();
	}
	else if (last == ')' && pila.top() == '(') {
		pila.pop();
	}
	else if (last == '}' && pila.top() == '{') {
		pila.pop();
	}
	else return false;

	return true;
}

bool resuelveCaso() {
	std::string input;

	getline(std::cin, input);

	if (!std::cin)return false;
	
	std::stack<char> pila;
	bool continuar = true;

	for (int i = 0; i < input.size() && continuar; i++){
		if (input[i] == '[' || input[i] == '(' || input[i] == '{'){
			pila.push(input[i]);
		}
		if (input[i] == ']' || input[i] == ')' || input[i] == '}'){
			pila.push(input[i]);
			continuar = equilibrado(pila);
		}
	}


	if (continuar && pila.empty()) std::cout << "YES\n";
	else std::cout << "NO\n";

	return true;
}

int main() {
	while (resuelveCaso());
}

