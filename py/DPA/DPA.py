from math import inf

def DPA(G, a, s):
    suma = 0           # Łączny koszt drzewa rozpinającego
    A = []             # Lista krawędzi należących do drzewa
    V = list(G.keys()) 
    alfa = [0 for _ in V]           # Tablica poprzedników wierzchołków
    beta = [inf for _ in V]         # Minimalne koszty dojścia do wierzchołków
    Q = V.copy()                    # Zbiór wierzchołków nieprzetworzonych
    N = [list(G[u]) for u in V]     # Lista sąsiadów dla każdego wierzchołka
    beta[s] = 0                     # Koszt dojścia do wierzchołka startowego
    Q.remove(s)                     
    us = s                          # Bieżący wierzchołek

    # Główna pętla algorytmu
    while Q:
        for u in Q:
            for u in N[us]:
                if a[u][us] < beta[u]:      # Aktualizacja kosztów dojścia
                    alfa[u] = us
                    beta[u] = a[u][us]
        
        # Wybór wierzchołka o minimalnym koszcie
        min_beta = inf
        for u in Q:
            if beta[u] < min_beta:
                min_beta = beta[u]
                us = u
        
        Q.remove(us)
        A.append((alfa[us], us))            # Dodanie krawędzi do drzewa
        suma += a[alfa[us]][us]             # Aktualizacja kosztu całkowitego

    return A, suma

graf = {
    0:[2,3,4,5,6,7],
    1:[2,8,9],
    2:[1,3,9,0],
    3:[2,4,9,0],
    4:[3,5,0],
    5:[4,6,0],
    6:[5,7,9,0],
    7:[6,8,9,0],
    8:[1,7,9],
    9:[1,2,3,6,7,8]
}

a = [
    [0,inf,3,2,2,2,2,3,inf,inf],
    [inf,0,1,inf,inf,inf,inf,inf,1,2],
    [3,1,0,1,inf,inf,inf,inf,inf,2],
    [2,inf,1,0,1,inf,inf,inf,inf,3],
    [2,inf,inf,1,0,1,inf,inf,inf,inf],
    [2,inf,inf,inf,1,0,1,inf,inf,inf],
    [2,inf,inf,inf,inf,1,0,1,inf,3],
    [3,inf,inf,inf,inf,inf,1,0,1,2],
    [inf,1,inf,inf,inf,inf,inf,1,0,2],
    [inf,2,2,3,inf,inf,3,2,2,0],
]
print("Minimalne drzewo rozpinające grafu, przy rozpoczęciu w wierzchołku 1")
print(DPA(graf, a, 1))