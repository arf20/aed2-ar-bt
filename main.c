#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} sol_t;

int
compare(const void* a, const void* b)
{
     int int_a = * ((int*) a);
     int int_b = * ((int*) b);
     
     if (int_a == int_b) return 0;
     else if (int_a < int_b) return -1;
     else return 1;
}

void
prints(int *s, int n)
{
    for (int i = 0; i < n; i++)
        printf("%2d ", s[i]);
}

int
sum(int *v, int n)
{
    int t = 0;
    for (int i = 0; i < n; i++)
        t += v[i];
    return t;
}

int
count(int *v, int n, int k)
{
    int t = 0;
    for (int i = 0; i < n; i++)
        t += (v[i] == k);
    return t;
}

sol_t bt(int *pesos, int n) {
    // ordenar
    qsort(pesos, n, sizeof(int), compare);

    int nivel = 0, voa = INT_MAX;

    int *s = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        s[i] = -1;

    int sumequipoA = 0, sumequipoB = 0;
    int solsumequipoA = 0, solsumequipoB = 0;

    size_t c = 0;

    while (nivel >= 0) {
        // generar
        //std::cout << nivel << std::endl;
        if (s[nivel] == 0)
            sumequipoA -= pesos[nivel];

        s[nivel]++;
        if (s[nivel] == 0)
            sumequipoA += pesos[nivel];
        else if (s[nivel] == 1)
            sumequipoB += pesos[nivel];

        int diff = abs(sumequipoA - sumequipoB);

#if 0
        printf("%2d: ", nivel);
        prints(s);
        printf(": %d, %d -> %d\n", sumequipoA, sumequipoB, diff);
#endif

        // solucion
        if (nivel == n - 1) {
            //std::cout << "sol" << std::endl;
            if (diff < voa) {
                voa = diff;
                solsumequipoA = sumequipoA;
                solsumequipoB = sumequipoB;
            }
        }
        // criterio
        if (
            (nivel != n - 1)
            && (sum(&pesos[nivel], n - nivel) > diff)                                   // mejora 1300%
            && (abs(count(s, n, 0) - count(s, n, 1)) < n - nivel)        // mejora 114%
        )
            nivel++;
        // retroceder
        else
            while (!(s[nivel] < 1) && nivel >= 0) {
                if (s[nivel] == 0)
                    sumequipoA -= pesos[nivel];
                else if (s[nivel] == 1)
                    sumequipoB -= pesos[nivel];
                s[nivel] = -1;
                nivel--;
            }

        c++;
    }

    //printf("%d\n", c);
    
    if (solsumequipoA > solsumequipoB) {
        return (sol_t){solsumequipoB, solsumequipoA};
    }
    
    return (sol_t){solsumequipoA, solsumequipoB};
}

/*
sol_t ar(std::vector<int> pesos) {
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
}*/

int main() {
    int casos;
    scanf("%d", &casos);

    for (; casos > 0; casos--) {
        int n;
        scanf("%d", &n);

        if (n == 0)
            continue;

        int *pesos = malloc(sizeof(int) * n);

        int t;
        for (int i = 0; i < n; i++) {
            scanf("%d", &t);
            pesos[i] = t;
        }

        sol_t sol = bt(pesos, n);

        printf("%d %d\n", sol.a, sol.b);
    }

}

