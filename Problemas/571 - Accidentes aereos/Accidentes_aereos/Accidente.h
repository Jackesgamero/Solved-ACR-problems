#ifndef Accidente_h
#define Accidente_h

#include <iostream>
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

	std::string get_fecha() const{
		return fecha;
	}
};

inline std::istream & operator>>(std::istream & in, accidente& a) {
	int m;
	std::string f;

	in >> f >> m;
	
	a = accidente(f, m);
	return in;
}

#endif /* Accidente_h */
