from typing import Dict, List 
from math import inf

def NN(G: Dict, w: List[List], s: int):
    n = len(G)                      # Liczba wierzchołków w grafie
    odwiedzone = [s]                # Lista odwiedzonych wierzchołków
    suma = 0                        # Całkowity koszt trasy
    nieodwiedzone = list(G.keys())  # Lista wierzchołków do odwiedzenia
    nieodwiedzone.remove(s)
    kolejny_wierzcholek = True

    while len(odwiedzone) < n:
        min_krawedz = inf
        v = None

        if not kolejny_wierzcholek:      # W przypadku braku dalszego sąsiada
            s = nieodwiedzone[0]         # Wybierz pierwszy nieodwiedzony wierzchołek
        
        for sasiad in G[s]:
            if sasiad in nieodwiedzone and w[s][sasiad] < min_krawedz:
                # Znaleziono lepszą (krótszą) krawędź
                min_krawedz = w[s][sasiad]
                v = sasiad
            elif sasiad in odwiedzone and s in nieodwiedzone:
                # Przypadek specjalny — odwiedzony sąsiad i nieodwiedzony wierzchołek
                suma += w[s][sasiad]
                odwiedzone.append(s)
                nieodwiedzone.remove(s)

        if v is not None:
            # Przejście do kolejnego wierzchołka
            s = v
            if s not in odwiedzone:
                odwiedzone.append(s)
                suma += min_krawedz
            nieodwiedzone.remove(s)
        else:
            kolejny_wierzcholek = False

    return odwiedzone, suma

# Graf 1
G = {
    0: [1,7],
    1: [0,2,6],
    2: [1,3,5],
    3: [2,4],
    4: [3,5],
    5: [2,4,6],
    6: [1,7,9],
    7: [0,6,8],
    8: [7,9],
    9: [6,8]
}
s = 0
w = [
    [0,2,inf,inf,inf,inf,inf,3,inf,inf],
    [2,0,2,inf,inf,inf,3,inf,inf,inf],
    [inf,2,0,2,inf,3,inf,inf,inf,inf],
    [inf,inf,2,0,3,inf,inf,inf,inf,inf],
    [inf,inf,inf,3,0,2,inf,inf,inf,inf],
    [inf,inf,3,inf,2,0,2,inf,inf,inf],
    [inf,3,inf,inf,inf,2,0,3,inf,2],
    [3,inf,inf,inf,inf,inf,3,0,2,inf],
    [inf,inf,inf,inf,inf,inf,inf,2,0,2],
    [inf,inf,inf,inf,inf,inf,2,inf,2,0],
]
# Graf 2
G2 = {
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
s2 = 1
w2 = [
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

print('Graf #1')
print(NN(G, w, s))
print('Graf #2')
print(NN(G2, w2, s2))
