//Autor : Jaime Martinez Gamero

#include <limits.h>
#include <iostream>
#include <queue>

bool resuelveCaso()
{
    size_t N;

    std::cin >> N;

    if (!std::cin) return false;

    std::priority_queue<int> PQ;
    std::priority_queue<int, std::vector<int>, std::greater<int>> PQ2;
   
    //tam1: elementos de PQ
    //tam2: elementos de PQ2
    //vacio: toma el valor 1 si nunca han llegado clientes y 0 en caso contrario
    //ultimo : ultimo elemento de PQ2
    int num, vacio = 1, ultimo, tam1 = 0, tam2 = 0, sol;

    //Indica si el carnicero nunca ha llamado sin clientes   
    bool primero = true;
      
    for (size_t i = 0; i < N; ++i){
         std::cin >> num;
         if (num == 0) {
            if (tam1 == 0 && tam2 == 0) {
                //Si llama sin clientes
                if (primero) {
                    primero = false; 
                    std::cout << "ECSA";
                }
                else std::cout << " ECSA";
            }
            else
            {
                if (tam2 > tam1) {
                    sol = PQ2.top();
                    PQ2.pop();
                    tam2--; 
                }
                else {
                    sol = PQ.top();
                    PQ.pop();
                    tam1--; 
                }
                primero = false;

                //Mostrar salida
                if (primero) std::cout << sol;
                else std::cout << " " << sol;
            }
         }
         else {
            if (vacio == 1) {
                PQ.push(num);
                vacio = 0;
                tam1++; 
            }
            else {
                 if (num < ultimo) { 
                     PQ.push(num);
                     tam1++; 
                 }
                 else { 
                     PQ2.push(num);
                     tam2++; 
                 }
            }
         }
         //Recolocar
         if (abs(tam1 - tam2) > 1) {
            if (tam1 > tam2) { num = PQ.top(); PQ.pop();  PQ2.push(num); tam1--; tam2++; }
            else { num = PQ2.top(); PQ2.pop();  PQ.push(num); tam2--; tam1++; }
         }
         if (tam2 != 0) ultimo = PQ2.top();
         else ultimo = INT_MAX;
        }
        std::cout << '\n';
    
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}