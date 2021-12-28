#include <iostream>
#include <vector>
#include <algorithm>

bool resuelveCaso() {
    std::vector<long long int> collar, sol;
    long long int perla;

    std::cin >> perla;

    if (perla == 0) return false;

    while (perla != 0) {
        collar.push_back(perla);
        std::cin >> perla;
    }

    for (long long int i = 0; i < collar.size(); ++i)
        sol.push_back(collar[i]);
    
    bool simetrico = true;
    sort(collar.begin(), collar.end());

    for (long long int i = 0; i < collar.size() && simetrico; ++i) {
        if (i % 2 == 1) {
            if (collar[i] != collar[i - 1] || collar.size() % 2 == 0) 
                simetrico = false;
        }
    }

    if (simetrico) {
        int pos = 0;
        for (int i = 0; i < collar.size(); i += 2) {
            if (i != collar.size() - 1) {
                sol[pos] = collar[i];
                sol[sol.size() - 1 - pos] = collar[i + 1];
            }
            else sol[pos] = collar[i];
            pos++;
        }
        for (long long int i = 0; i < sol.size(); ++i) {
            if (i != sol.size() - 1) std::cout << sol[i] << " ";
            else std::cout << sol[i];
        }
        std::cout << '\n';
    }
    else std::cout << "NO\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
