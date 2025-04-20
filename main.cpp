#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <iomanip>

void prints(std::vector<int>& s) {
    for (int& t : s)
        std::cout << std::setw(2) << t << " ";
}

std::pair<int, int> bt(std::vector<int> pesos) {
    auto type = decltype(pesos)::value_type(0);
    int n = pesos.size();
    // ordenar
    std::sort(pesos.begin(), pesos.end(), std::greater<int>());

    int nivel = 0, voa = INT_MAX;

    std::vector<int> s(n, -1);

    int pesoActA = 0, pesoActB = 0;
    int pesoOptA = 0, pesoOptB = 0;

    size_t c = 0;

    while (nivel >= 0) {
        // generar
        //std::cout << nivel << std::endl;
        if (s[nivel] == 0)
            pesoActA -= pesos[nivel];

        s[nivel]++;
        if (s[nivel] == 0)
            pesoActA += pesos[nivel];
        else if (s[nivel] == 1)
            pesoActB += pesos[nivel];

        int diff = std::abs(pesoActA - pesoActB);

#if 0
        std::cout << std::setw(2) << nivel << ": ";
        prints(s);
        std::cout << ": " << pesoActA << ", " << pesoActB << " -> " << diff << std::endl;
#endif

        // solucion
        if (nivel == n - 1) {
            //std::cout << "sol" << std::endl;
            if (diff < voa) {
                voa = diff;
                pesoOptA = pesoActA;
                pesoOptB = pesoActB;
            }
        }
        // criterio
        if (
            (nivel != n - 1)
            //&& (std::accumulate(pesos.begin() + nivel, pesos.end(), type) > diff)                                   // mejora 1300%
            //&& (std::abs(std::count(s.begin(), s.end(), 0) - std::count(s.begin(), s.end(), 1)) < n - nivel)        // mejora 114%
        )
            nivel++;
        // retroceder
        else
            while (!(s[nivel] < 1) && nivel >= 0) {
                if (s[nivel] == 0)
                    pesoActA -= pesos[nivel];
                else if (s[nivel] == 1)
                    pesoActB -= pesos[nivel];
                s[nivel] = -1;
                nivel--;
            }

        c++;
    }

    std::cerr << c << ",";
    
    if (pesoOptA > pesoOptB)
        std::swap(pesoOptA, pesoOptB);
    
    return std::pair<int, int>(pesoOptA, pesoOptB);
}

std::pair<int, int> ar(std::vector<int> pesos) {
    auto type = decltype(pesos)::value_type(0);
    // ordenar
    std::sort(pesos.begin(), pesos.end(), std::greater<int>());
    
    std::vector<int> equipoA, equipoB;
    while (pesos.size() > 0) {
        if (    std::accumulate(equipoA.begin(), equipoA.end(), type)
            <   std::accumulate(equipoB.begin(), equipoB.end(), type)
        )
            equipoA.push_back(pesos[0]);
        else
            equipoB.push_back(pesos[0]);
        pesos.erase(pesos.begin());
    }
    
    return std::pair<int, int>{std::accumulate(equipoA.begin(), equipoA.end(), type),
        std::accumulate(equipoB.begin(), equipoB.end(), type)};
}

int main() {
    std::cout << std::setw(3);

    int casos;
    std::cin >> casos;

    for (; casos > 0; casos--) {
        int n;
        std::cin >> n;

        if (n == 0)
            continue;

        std::vector<int> pesos;

        int t;
        for (int i = 0; i < n; i++) {
            std::cin >> t;
            pesos.push_back(t);
        }

        std::cerr << n << ",";
        auto sol = bt(pesos);
        std::cerr << std::endl;

        std::cout << sol.first << " " << sol.second << std::endl;

    }

}

