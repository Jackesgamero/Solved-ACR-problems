#include <iostream>
#include <stack>
#include <string>

class accidente {
private:
	int muertos;
	std::string fecha;

public:
	accidente() { muertos = 0; fecha = ""; }

	accidente(std::string f, int m) {
		muertos = m;
		fecha = f;
	}

	int get_muertos() const {
		return muertos;
	}

	std::string get_fecha() const {
		return fecha;
	}
};

inline std::istream& operator>>(std::istream& in, accidente& a) {
	int m;
	std::string f;

	in >> f >> m;

	a = accidente(f, m);
	return in;
}

bool resuelveCaso() {
	size_t num;
	std::cin >> num;

	if (!std::cin) return false;
	
	std::stack <accidente> pila;
	accidente a("", 0);
	bool encontrado = false;

	for (size_t i = 0; i < num; ++i){

		encontrado = false;

		std::cin >> a;

		if (pila.empty()){
			std::cout << "NO HAY\n";
			pila.push(a);
		}
		else{
			if (a.get_muertos() < pila.top().get_muertos()){
				std::cout << pila.top().get_fecha() << "\n";
				pila.push(a);
			}
			else{
				pila.pop();

				while (!pila.empty() && !encontrado) {
					
					if (a.get_muertos() < pila.top().get_muertos()){
						std::cout << pila.top().get_fecha() << "\n";
						encontrado = true;
						pila.push(a);
					}
					else{
						pila.pop();
					}
				}

				if (!encontrado){
					std::cout << "NO HAY\n";
					pila.push(a);
				}
			}
		}
	}

	std::cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
}