#include <iostream>
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move

template <class T>
class set {
public:
    set(int tam = TAM_INICIAL); // constructor
    set(set<T> const& other); // constructor por copia
    set<T>& operator=(set<T> const& other); // operador de asignación
    ~set(); // destructor
    void insert(T e);
    bool contains(T e) const;
    void erase(T e);
    bool empty() const;
    int size() const;
private:
    const static int TAM_INICIAL = 8;
    int contador;
    int capacidad;
    T* datos;
    void amplia();
    void libera();
    void copia(set<T> const& other);
};

template <class T>
set<T>::set(int tam) : contador(0), capacidad(tam), datos(new T[capacidad]) {}

template <class T>
set<T>::~set() {
    libera();
}

template <class T>
void set<T>::libera() {
    delete[] datos;
}

/** Constructor por copia */
template <class T>
set<T>::set(set<T> const& other) {
    copia(other);
}

/** Operador de asignación */
template <class T>
set<T>& set<T>::operator=(set<T> const& other) {
    if (this != &other) {
        libera();
        copia(other);
    }
    return *this;
}

template <class T>
void set<T>::copia(set<T> const& other) {
    capacidad = other.capacidad;
    contador = other.contador;
    datos = new T[capacidad];
    for (int i = 0; i < contador; ++i)
        datos[i] = other.datos[i];
}

template <class T>
void set<T>::insert(T e) {
    if (!contains(e)) {
        if (contador == capacidad)
            amplia();
        datos[contador] = e;
        ++contador;
    }
}

template <class T>
bool set<T>::contains(T e) const {
    int i = 0;
    while (i < contador && datos[i] != e)
        ++i;
    return i < contador;
}

template <class T>
void set<T>::amplia() {
    T* nuevos = new T[2 * capacidad];
    for (int i = 0; i < capacidad; ++i)
        nuevos[i] = std::move(datos[i]);
    delete[] datos;
    datos = nuevos;
    capacidad *= 2;
}

template <class T>
void set<T>::erase(T e) {
    int i = 0;
    while (i < contador && datos[i] != e)
        ++i;
    if (i < contador) {
        datos[i] = datos[contador - 1];
        --contador;
    }
    else
        throw std::domain_error("El elemento no esta");
}


template <class T>
bool set<T>::empty() const {
    return contador == 0;
}

template <class T>
int set<T>::size() const {
    return contador;
}

int siguiente(int n, const set<int> s) {
	int suma = 0;
	while (n > 0) {
		int d = n % 10;
		suma += d * d * d;
		n /= 10;
	}
	if (suma == 1) {
		std::cout << "- 1 -> cubifinito.\n";
	}
	else if (s.contains(suma)) {
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
		set<int> s;

		std::cout << n << ' ';
		while (n != 1 && !s.contains(n)) {
			s.insert(n);
			n = siguiente(n, s);
		}
	}

	return true;
}

int main() {
	while (resuelveCaso());
}

